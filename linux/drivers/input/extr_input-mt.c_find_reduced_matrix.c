#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */

/* Variables and functions */
 scalar_t__ adjust_dual (int*,int,int*,int,int) ; 

__attribute__((used)) static void find_reduced_matrix(int *w, int nr, int nc, int nrc, int mu)
{
	int i, k, sum;

	for (k = 0; k < nrc; k++) {
		for (i = 0; i < nr; i++)
			adjust_dual(w + i, nr, w + i + nrc, nr <= nc, mu);
		sum = 0;
		for (i = 0; i < nrc; i += nr)
			sum += adjust_dual(w + i, 1, w + i + nr, nc <= nr, mu);
		if (!sum)
			break;
	}
}