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
 int HALFLIFE ; 
 long SHIFT ; 
 long max ; 
 int n ; 
 int /*<<< orphan*/  printf (char*,long) ; 
 unsigned long y ; 

void calc_converged_max(void)
{
	long last = 0, y_inv = ((1UL<<32)-1)*y;

	for (; ; n++) {
		if (n > -1)
			max = ((max*y_inv)>>SHIFT) + 1024;
			/*
			 * This is the same as:
			 * max = max*y + 1024;
			 */

		if (last == max)
			break;

		last = max;
	}
	n--;
	printf("#define LOAD_AVG_PERIOD %d\n", HALFLIFE);
	printf("#define LOAD_AVG_MAX %ld\n", max);
//	printf("#define LOAD_AVG_MAX_N %d\n\n", n);
}