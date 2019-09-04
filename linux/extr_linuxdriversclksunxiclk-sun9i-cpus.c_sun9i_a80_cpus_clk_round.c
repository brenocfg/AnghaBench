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
typedef  scalar_t__ u8 ;

/* Variables and functions */
 scalar_t__ DIV_ROUND_UP (scalar_t__,int) ; 
 scalar_t__ SUN9I_CPUS_MUX_PARENT_PLL4 ; 

__attribute__((used)) static long sun9i_a80_cpus_clk_round(unsigned long rate, u8 *divp, u8 *pre_divp,
				     u8 parent, unsigned long parent_rate)
{
	u8 div, pre_div = 1;

	/*
	 * clock can only divide, so we will never be able to achieve
	 * frequencies higher than the parent frequency
	 */
	if (parent_rate && rate > parent_rate)
		rate = parent_rate;

	div = DIV_ROUND_UP(parent_rate, rate);

	/* calculate pre-divider if parent is pll4 */
	if (parent == SUN9I_CPUS_MUX_PARENT_PLL4 && div > 4) {
		/* pre-divider is 1 ~ 32 */
		if (div < 32) {
			pre_div = div;
			div = 1;
		} else if (div < 64) {
			pre_div = DIV_ROUND_UP(div, 2);
			div = 2;
		} else if (div < 96) {
			pre_div = DIV_ROUND_UP(div, 3);
			div = 3;
		} else {
			pre_div = DIV_ROUND_UP(div, 4);
			div = 4;
		}
	}

	/* we were asked to pass back divider values */
	if (divp) {
		*divp = div - 1;
		*pre_divp = pre_div - 1;
	}

	return parent_rate / pre_div / div;
}