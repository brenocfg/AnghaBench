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
typedef  unsigned long u32 ;
struct clk_hw {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static long clk_pllv3_sys_round_rate(struct clk_hw *hw, unsigned long rate,
				     unsigned long *prate)
{
	unsigned long parent_rate = *prate;
	unsigned long min_rate = parent_rate * 54 / 2;
	unsigned long max_rate = parent_rate * 108 / 2;
	u32 div;

	if (rate > max_rate)
		rate = max_rate;
	else if (rate < min_rate)
		rate = min_rate;
	div = rate * 2 / parent_rate;

	return parent_rate * div / 2;
}