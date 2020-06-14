#include <iostream>
#include <vector>
#include <fstream>
using namespace std;

vector<int> cost(10001);

void readCost(const string& costFile) {
	ifstream file(costFile);
	for(int i = 0; i < cost.size(); i++) {
		int n, c;
		file >> n >> c;
		cost[i] = c;
	}
}

void printMat(const vector<vector<int> >& mat) {
	for(int i = 0; i < mat.size(); i++) {
		for(int j = 0; j < mat[i].size(); j++) {
			cout << mat[i][j] << ' ';
		}
		cout << endl;
	}
	cout << endl;
}

void printBT(const vector<vector<pair<int, int> > >& mat ) {
	for(int i = 0; i < mat.size(); i++) {
			for(int j = 0; j < mat[i].size(); j++) {
				cout << '(' << mat[i][j].first << ',' << mat[i][j].second << ')' << ' ';
			}
			cout << endl;
		}
		cout << endl;
}


int solve(int N, int A, int B) {
	vector<vector<int> > dp(N, vector<int>(B+1));
	vector<vector<pair<int, int> > > bt(N, vector<pair<int, int> >(B + 1));
	for(int j = 0; j <= B; j++) {
		dp[0][j] = cost[A + j];
		bt[0][j].first = A + j;
		bt[0][j].second = -1;
	}
	for(int i = 1; i < N; i++) {
		for(int m = 0 ; m < B + 1; m++) {
			dp[i][m] = INT16_MAX;
			for(int n = 0; n <= min(B, A + m); n++) {
				if (dp[i][m] > dp[i-1][n] + cost[A + m - n]) {
					dp[i][m] = dp[i-1][n] + cost[A + m - n];
					bt[i][m].first = A + m - n;
					bt[i][m].second = n;
				}
			}
		}
	}
	//printMat(dp);
	//printBT(bt);
	vector<int> cheques(N);
	int i = 0;
	int j = N - 1;
	while(i != -1) {
		cheques[j] = bt[j][i].first;
		i = bt[j][i].second;
		--j;
	}

	for(int l = 0; l < N; l++) {
		cout << cheques[l] << ' ';
	}
	cout << endl;
	return dp[N-1][0];
}

int main(int argc, char * argv[]) {
    
	string input(argv[1]);
	string output(argv[2]);
	string costFile(argv[3]);

	readCost(costFile);

	vector<int> solutions;

	ifstream inFile(input);
	ofstream oFile(output);
	int T;
	inFile >> T;
	for(int t = 0; t < T; t++) {
		int N, A, B;
		inFile >> N >> A >> B;
		//cout << "test case " << t + 1 << ". Solving for: " << N << ' ' << A << ' ' << B << endl;
		int sol = solve(N, A, B);
		//cout << "cost: " << endl << sol << endl;
		solutions.push_back(sol);
		oFile << sol;
		if( t != T - 1) {
			oFile << endl;
		}
	}
	return 0;
}
