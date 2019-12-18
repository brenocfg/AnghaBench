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
typedef  int u64 ;
typedef  int u32 ;

/* Variables and functions */
 int /*<<< orphan*/  check_clock (int,int,int,int,int*,int*,int*) ; 
 int /*<<< orphan*/  do_div (int,int) ; 
 int ixp4xx_timer_freq ; 

__attribute__((used)) static void find_best_clock(u32 rate, u32 *best, u32 *reg)
{
	u32 a, b, diff = 0xFFFFFFFF;

	a = ixp4xx_timer_freq / rate;

	if (a > 0x3FF) { /* 10-bit value - we can go as slow as ca. 65 kb/s */
		check_clock(rate, 0x3FF, 1, 1, best, &diff, reg);
		return;
	}
	if (a == 0) { /* > 66.666 MHz */
		a = 1; /* minimum divider is 1 (a = 0, b = 1, c = 1) */
		rate = ixp4xx_timer_freq;
	}

	if (rate * a == ixp4xx_timer_freq) { /* don't divide by 0 later */
		check_clock(rate, a - 1, 1, 1, best, &diff, reg);
		return;
	}

	for (b = 0; b < 0x400; b++) {
		u64 c = (b + 1) * (u64)rate;
		do_div(c, ixp4xx_timer_freq - rate * a);
		c--;
		if (c >= 0xFFF) { /* 12-bit - no need to check more 'b's */
			if (b == 0 && /* also try a bit higher rate */
			    !check_clock(rate, a - 1, 1, 1, best, &diff, reg))
				return;
			check_clock(rate, a, b, 0xFFF, best, &diff, reg);
			return;
		}
		if (!check_clock(rate, a, b, c, best, &diff, reg))
			return;
		if (!check_clock(rate, a, b, c + 1, best, &diff, reg))
			return;
	}
}