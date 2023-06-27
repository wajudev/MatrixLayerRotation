#include <iostream>

#include "bits/stdc++.h"

using namespace std;

string ltrim(const string &);

string rtrim(const string &);

vector<string> split(const string &);

/*
* Complete the 'matrixRotation' function below.
*
*  The function accepts following parameters:
*  1. 2D_INTEGER_ARRAY matrix
*  2. INTEGER r
*/

void printMatrix(const vector<vector<int>> &matrix, unsigned long m, unsigned long n) {
    cout << "-----------------------------------" << endl;
    for (unsigned long i = 0; i < m; ++i) {
        for (unsigned long j = 0; j < n; ++j) {
            cout << matrix[i][j] << ' ';
        }
        cout << endl;
    }
}

void matrixRotation(vector<vector<int>> &matrix, int r) {
    unsigned long m = matrix.size();
    unsigned long n = matrix[0].size();

    // Calculate the number of layers
    unsigned long layers = min(m, n) / 2;

    // Rotate each layer
    for (unsigned long layer = 0; layer < layers; ++layer) {
        // Calculate the number of elements in the current layer
        unsigned long layer_length = 2 * (m - 2 * layer) + 2 * (n - 2 * layer) - 4;

        // Calculate the number of rotations
        unsigned long rotations = r % layer_length;

        // Rotate the layer elements
        vector<int> temp(layer_length);

        // Store the layer elements in a temporary vector
        unsigned long idx = 0;

        // Top row
        for (unsigned long j = layer; j < n - layer; ++j) {
            temp[idx++] = matrix[layer][j];
        }

        // Right column
        for (unsigned long i = layer + 1; i < m - layer - 1; ++i) {
            temp[idx++] = matrix[i][n - layer - 1];
        }

        // Bottom row
        for (unsigned long j = n - layer - 1; j > layer; --j) {
            temp[idx++] = matrix[m - layer - 1][j];
        }

        // Left column
        for (unsigned long i = m - layer - 1; i > layer; --i) {
            temp[idx++] = matrix[i][layer];
        }

        // Rotate the temporary vector
        rotate(temp.begin(), temp.begin() + rotations, temp.end());

        // Assign the rotated values back to the matrix
        idx = 0;

        // Top row
        for (unsigned long j = layer; j < n - layer; ++j) {
            matrix[layer][j] = temp[idx++];
        }

        // Right column
        for (unsigned long i = layer + 1; i < m - layer - 1; ++i) {
            matrix[i][n - layer - 1] = temp[idx++];
        }

        // Bottom row
        for (unsigned long j = n - layer - 1; j > layer; --j) {
            matrix[m - layer - 1][j] = temp[idx++];
        }

        // Left column
        for (unsigned long i = m - layer - 1; i > layer; --i) {
            matrix[i][layer] = temp[idx++];
        }
    }
}

int main() {
    string first_multiple_input_temp;
    getline(cin, first_multiple_input_temp);

    vector<string> first_multiple_input = split(rtrim(first_multiple_input_temp));

    int m = stoi(first_multiple_input[0]);

    int n = stoi(first_multiple_input[1]);

    int r = stoi(first_multiple_input[2]);

    vector<vector<int>> matrix(m);

    for (int i = 0; i < m; i++) {
        matrix[i].resize(n);

        string matrix_row_temp_temp;
        getline(cin, matrix_row_temp_temp);

        vector<string> matrix_row_temp = split(rtrim(matrix_row_temp_temp));

        for (int j = 0; j < n; j++) {
            int matrix_row_item = stoi(matrix_row_temp[j]);

            matrix[i][j] = matrix_row_item;
        }
    }

    matrixRotation(matrix, r);
    printMatrix(matrix, m, n);

    return 0;
}

string ltrim(const string &str) {
    string s(str);

    s.erase(
            s.begin(),
            find_if(s.begin(), s.end(), not1(ptr_fun<int, int>(isspace)))
    );

    return s;
}

string rtrim(const string &str) {
    string s(str);

    s.erase(
            find_if(s.rbegin(), s.rend(), not1(ptr_fun<int, int>(isspace))).base(),
            s.end()
    );

    return s;
}

vector<string> split(const string &str) {
    vector<string> tokens;

    string::size_type start = 0;
    string::size_type end = 0;

    while ((end = str.find(" ", start)) != string::npos) {
        tokens.push_back(str.substr(start, end - start));

        start = end + 1;
    }

    tokens.push_back(str.substr(start));

    return tokens;
}

