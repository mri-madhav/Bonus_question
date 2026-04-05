#include <bits/stdc++.h>
using namespace std;

int k = 1; // set to 7 for Part B

// total cells = 28
vector<int> grid(28, 0);
vector<bool> used(60, false);

int best = INT_MAX;

// ----------- DEFINE THE 4 SQUARES -----------
// NOTE: These indices correspond to a fixed mapping of the 28-cell layout
vector<vector<int>> squares = {
    {0,1,2,3,4,5,8,9,10},         // top square
    {3,4,5,8,9,10,13,14,15},      // upper-middle
    {4,5,6,9,10,11,14,15,16},     // right-middle
    {13,14,15,18,19,20,23,24,25}  // bottom square
};

// ----------- CHECK A FULL 3x3 SQUARE -----------
bool validSquare(const vector<int>& sq) {
    vector<int> sums;

    // rows
    sums.push_back(grid[sq[0]] + grid[sq[1]] + grid[sq[2]]);
    sums.push_back(grid[sq[3]] + grid[sq[4]] + grid[sq[5]]);
    sums.push_back(grid[sq[6]] + grid[sq[7]] + grid[sq[8]]);

    // columns
    sums.push_back(grid[sq[0]] + grid[sq[3]] + grid[sq[6]]);
    sums.push_back(grid[sq[1]] + grid[sq[4]] + grid[sq[7]]);
    sums.push_back(grid[sq[2]] + grid[sq[5]] + grid[sq[8]]);

    // diagonals
    sums.push_back(grid[sq[0]] + grid[sq[4]] + grid[sq[8]]);
    sums.push_back(grid[sq[2]] + grid[sq[4]] + grid[sq[6]]);

    int mn = *min_element(sums.begin(), sums.end());
    int mx = *max_element(sums.begin(), sums.end());

    return (mx - mn <= k);
}

// ----------- CHECK ONLY COMPLETED SQUARES (PRUNING) -----------
bool checkPartial() {
    for (auto &sq : squares) {
        bool full = true;

        for (int idx : sq) {
            if (grid[idx] == 0) {
                full = false;
                break;
            }
        }

        if (full && !validSquare(sq)) return false;
    }
    return true;
}

// ----------- BACKTRACKING -----------
void dfs(int idx, int current_sum) {

    // pruning: if already worse, stop
    if (current_sum >= best) return;

    // all cells filled
    if (idx == 28) {
        best = min(best, current_sum);
        cout << "Found better sum: " << best << "\n";
        return;
    }

    // try small numbers first
    for (int num = 1; num <= 40; num++) {

        if (used[num]) continue;

        // assign
        grid[idx] = num;
        used[num] = true;

        // check constraints early
        if (checkPartial()) {
            dfs(idx + 1, current_sum + num);
        }

        // backtrack
        grid[idx] = 0;
        used[num] = false;
    }
}

// ----------- MAIN -----------
int main() {
    dfs(0, 0);

    cout << "Minimum sum = " << best << endl;
    return 0;
}