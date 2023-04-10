#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <math.h>
#include <memory.h>

int n, k;
double w[1003][1003];
int queue[2001], front, rear, dist[1003];
struct station {
	int x, y;
} s[1003];

double distance(int from, int to)
{
	int dx, dy;
	dx = s[from].x - s[to].x;
	dy = s[from].y - s[to].y;
	return sqrt(dx * dx + dy * dy);
}

void input()
{
	int i, j;
	scanf("%d %d", &n, &k);
	for (i = 1; i <= n; i++)
		scanf("%d %d", &s[i].x, &s[i].y);
	s[0].x = s[0].y = 0;
	s[n + 1].x = s[n + 1].y = 10000;

	for (i = 0; i <= n; i++)
		for (j = i + 1; j <= n + 1; j++)
			w[i][j] = w[j][i] = distance(i, j);
}

bool reachable(int upper_dist)
{
	int i, parent;
	memset(dist, 0, sizeof(dist));
	front = rear = 0;
	queue[++rear] = 0, dist[0] = 1; // start point (0, 0) with index 0
	do {
		parent = queue[++front];
		for (i = 1; i <= n + 1; i++)
			if (!dist[i] && w[parent][i] <= (double)upper_dist)
			{
				queue[++rear] = i;
				dist[i] = dist[parent] + 1;
			}
	} while (front != rear);
	return (dist[n + 1] && dist[n + 1] <= k + 2); // including start and end points
}

int main()
{
	input();
	int mid, left, right;
	left = 1, right = 14143; // 10000*sqrt(2)
	while (left <= right)
	{
		mid = (left + right) / 2;
		if (reachable(mid))
		{
			if (!reachable(mid - 1))
			{
				printf("%d", (mid % 10 ? mid / 10 + 1 : mid / 10));
				return 0;
			}
			right = mid - 1;
		}
		else
			left = mid + 1;
	}
	return 0;
}