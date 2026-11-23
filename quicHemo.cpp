#include <bits/stdc++.h>
using namespace std;

const int N = 6;
const int B = 4;

string locations[N] = {
    "Rajshahi Medical",
    "Varendra Hospital",
    "Padma Blood Bank",
    "Meghna Blood Bank",
    "Jamuna Blood Bank",
    "Korotoa Blood Bank"
};

string bloodGroups[8] = {
    "A+", "A-", "B+", "B-",
    "AB+", "AB-", "O+", "O-"
};

int stock[B][8] = {
    {5, 2, 1, 3, 2, 1, 6, 2},
    {3, 1, 4, 2, 1, 2, 5, 3},
    {2, 3, 2, 1, 4, 1, 3, 2},
    {6, 2, 5, 3, 2, 2, 7, 4}
};

int graph[N][N] = {
    {0, 0, 4, 7, 0, 9},
    {0, 0, 3, 0, 6, 5},
    {4, 3, 0, 2, 5, 0},
    {7, 0, 2, 0, 3, 6},
    {0, 6, 5, 3, 0, 2},
    {9, 5, 0, 6, 2, 0}
};

int bankLocation[B] = {2, 3, 4, 5};

void showLocations()
{
    cout << "\nLocations:\n";

    for (int i = 0; i < N; i++)
    {
        cout << i << ". " << locations[i] << endl;
    }
}

void showBloodGroups()
{
    cout << "\nBlood Groups:\n";

    for (int i = 0; i < 8; i++)
    {
        cout << i << ". " << bloodGroups[i] << endl;
    }
}

void showStock()
{
    cout << "\n===== BLOOD BANK STOCK =====\n";

    for (int i = 0; i < B; i++)
    {
        cout << "\n" << locations[bankLocation[i]] << endl;

        for (int j = 0; j < 8; j++)
        {
            cout << bloodGroups[j] << ": "
                 << stock[i][j] << " units\n";
        }
    }
}

void dijkstra(int source, int dist[], int parent[])
{
    bool visited[N] = {false};

    for (int i = 0; i < N; i++)
    {
        dist[i] = INT_MAX;
        parent[i] = -1;
    }

    dist[source] = 0;

    for (int i = 0; i < N; i++)
    {
        int u = -1;

        for (int j = 0; j < N; j++)
        {
            if (!visited[j] &&
                (u == -1 || dist[j] < dist[u]))
            {
                u = j;
            }
        }

        if (u == -1 || dist[u] == INT_MAX)
            break;

        visited[u] = true;

        for (int v = 0; v < N; v++)
        {
            if (graph[u][v] > 0 && !visited[v])
            {
                if (dist[u] + graph[u][v] < dist[v])
                {
                    dist[v] = dist[u] + graph[u][v];
                    parent[v] = u;
                }
            }
        }
    }
}

void showPath(int parent[], int destination)
{
    if (parent[destination] == -1)
    {
        cout << locations[destination];
        return;
    }

    showPath(parent, parent[destination]);

    cout << " -> " << locations[destination];
}

void bloodRequest()
{
    showLocations();

    int hospital;

    cout << "\nEnter hospital location number: ";
    cin >> hospital;

    if (hospital < 0 || hospital >= 2)
    {
        cout << "Invalid hospital location!\n";
        return;
    }

    showBloodGroups();

    int group;

    cout << "\nEnter blood group number: ";
    cin >> group;

    if (group < 0 || group >= 8)
    {
        cout << "Invalid blood group!\n";
        return;
    }

    int units;

    cout << "Enter required units: ";
    cin >> units;

    if (units <= 0)
    {
        cout << "Invalid unit amount!\n";
        return;
    }

    int dist[N], parent[N];

    dijkstra(hospital, dist, parent);

    vector<pair<int, int>> candidates;

    for (int i = 0; i < B; i++)
    {
        int location = bankLocation[i];

        if (stock[i][group] >= units &&
            dist[location] != INT_MAX)
        {
            candidates.push_back({dist[location], i});
        }
    }

    if (candidates.empty())
    {
        cout << "\nNo blood bank has enough available stock.\n";
        return;
    }

    sort(candidates.begin(), candidates.end());

    int selectedBank = candidates[0].second;
    int selectedLocation = bankLocation[selectedBank];

    int previousStock = stock[selectedBank][group];

    cout << "\n===== BLOOD REQUEST =====\n";

    cout << "\nSelected Blood Bank: "
         << locations[selectedLocation];

    cout << "\nBlood Group: "
         << bloodGroups[group];

    cout << "\nRequested Units: "
         << units;

    cout << "\nDistance: "
         << dist[selectedLocation] << " km";

    cout << "\nRoute: ";
    showPath(parent, selectedLocation);

    cout << "\nPrevious Stock: "
         << previousStock << " units";

    stock[selectedBank][group] -= units;

    cout << "\n\nBlood request successful!";

    cout << "\nRemaining Stock: "
         << stock[selectedBank][group] << " units\n";
}

// BFS Algorithm
void bfs(int source)
{
    bool visited[N] = {false};

    queue<int> q;

    visited[source] = true;
    q.push(source);

    cout << "\n===== REACHABLE LOCATIONS =====\n";

    while (!q.empty())
    {
        int u = q.front();
        q.pop();

        cout << locations[u] << endl;

        for (int v = 0; v < N; v++)
        {
            if (graph[u][v] > 0 && !visited[v])
            {
                visited[v] = true;
                q.push(v);
            }
        }
    }
}

// Prim's Minimum Spanning Tree
void prim()
{
    bool visited[N] = {false};

    int totalCost = 0;
    int edges = 0;

    visited[0] = true;

    cout << "\n===== MINIMUM NETWORK CONNECTIONS =====\n";

    while (edges < N - 1)
    {
        int minimum = INT_MAX;
        int u = -1, v = -1;

        for (int i = 0; i < N; i++)
        {
            if (visited[i])
            {
                for (int j = 0; j < N; j++)
                {
                    if (!visited[j] &&
                        graph[i][j] > 0 &&
                        graph[i][j] < minimum)
                    {
                        minimum = graph[i][j];
                        u = i;
                        v = j;
                    }
                }
            }
        }

        if (u == -1)
        {
            cout << "Network is disconnected!\n";
            return;
        }

        cout << locations[u] << " - "
             << locations[v] << " : "
             << minimum << " km\n";

        visited[v] = true;

        totalCost += minimum;
        edges++;
    }

    cout << "\nTotal Network Cost: "
         << totalCost << " km\n";
}

int main()
{
    int choice;

    do
    {
        cout << "\n\n============================================";
        cout << "\n   EMERGENCY BLOOD BANK & HOSPITAL NETWORK";
        cout << "\n============================================";

        cout << "\n1. Request Blood and Find Nearest Blood Bank";
        cout << "\n2. Show Reachable Locations (BFS)";
        cout << "\n3. Show Blood Bank Stock";
        cout << "\n4. View Minimum Network Connections";
        cout << "\n5. Exit";

        cout << "\n\nEnter your choice: ";

        cin >> choice;

        switch (choice)
        {
            case 1:
                bloodRequest();
                break;

            case 2:
            {
                showLocations();

                int source;

                cout << "\nEnter starting location number: ";
                cin >> source;

                if (source >= 0 && source < N)
                {
                    bfs(source);
                }
                else
                {
                    cout << "Invalid location!\n";
                }

                break;
            }

            case 3:
                showStock();
                break;

            case 4:
                prim();
                break;

            case 5:
                cout << "\nProgram ended.\n";
                break;

            default:
                cout << "\nInvalid choice!\n";
        }

    } while (choice != 5);

    return 0;
}