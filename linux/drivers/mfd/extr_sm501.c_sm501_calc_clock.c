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
struct sm501_clock {unsigned long mclk; int divider; int shift; } ;

/* Variables and functions */
 unsigned long DIV_ROUND_CLOSEST (unsigned long,int) ; 

__attribute__((used)) static int sm501_calc_clock(unsigned long freq,
			    struct sm501_clock *clock,
			    int max_div,
			    unsigned long mclk,
			    long *best_diff)
{
	int ret = 0;
	int divider;
	int shift;
	long diff;

	/* try dividers 1 and 3 for CRT and for panel,
	   try divider 5 for panel only.*/

	for (divider = 1; divider <= max_div; divider += 2) {
		/* try all 8 shift values.*/
		for (shift = 0; shift < 8; shift++) {
			/* Calculate difference to requested clock */
			diff = DIV_ROUND_CLOSEST(mclk, divider << shift) - freq;
			if (diff < 0)
				diff = -diff;

			/* If it is less than the current, use it */
			if (diff < *best_diff) {
				*best_diff = diff;

				clock->mclk = mclk;
				clock->divider = divider;
				clock->shift = shift;
				ret = 1;
			}
		}
	}

	return ret;
}