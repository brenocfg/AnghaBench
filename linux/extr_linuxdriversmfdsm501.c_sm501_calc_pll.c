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
struct sm501_clock {unsigned int m; unsigned int n; unsigned int k; unsigned long mclk; unsigned long divider; unsigned long shift; } ;

/* Variables and functions */
 scalar_t__ sm501_calc_clock (unsigned long,struct sm501_clock*,int,unsigned long,long*) ; 

__attribute__((used)) static unsigned long sm501_calc_pll(unsigned long freq,
					struct sm501_clock *clock,
					int max_div)
{
	unsigned long mclk;
	unsigned int m, n, k;
	long best_diff = 999999999;

	/*
	 * The SM502 datasheet doesn't specify the min/max values for M and N.
	 * N = 1 at least doesn't work in practice.
	 */
	for (m = 2; m <= 255; m++) {
		for (n = 2; n <= 127; n++) {
			for (k = 0; k <= 1; k++) {
				mclk = (24000000UL * m / n) >> k;

				if (sm501_calc_clock(freq, clock, max_div,
						     mclk, &best_diff)) {
					clock->m = m;
					clock->n = n;
					clock->k = k;
				}
			}
		}
	}

	/* Return best clock. */
	return clock->mclk / (clock->divider << clock->shift);
}