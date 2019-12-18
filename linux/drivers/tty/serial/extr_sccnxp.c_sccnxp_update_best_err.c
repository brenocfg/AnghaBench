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
 int abs (int) ; 

__attribute__((used)) static int sccnxp_update_best_err(int a, int b, int *besterr)
{
	int err = abs(a - b);

	if (*besterr > err) {
		*besterr = err;
		return 0;
	}

	return 1;
}