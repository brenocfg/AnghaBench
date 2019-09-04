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
struct mmp_clk_mix {int div_flags; struct clk_div_table* div_table; } ;
struct clk_div_table {unsigned int div; unsigned int val; } ;

/* Variables and functions */
 int CLK_DIVIDER_ONE_BASED ; 
 int CLK_DIVIDER_POWER_OF_TWO ; 

__attribute__((used)) static unsigned int _get_div(struct mmp_clk_mix *mix, unsigned int val)
{
	struct clk_div_table *clkt;

	if (mix->div_flags & CLK_DIVIDER_ONE_BASED)
		return val;
	if (mix->div_flags & CLK_DIVIDER_POWER_OF_TWO)
		return 1 << val;
	if (mix->div_table) {
		for (clkt = mix->div_table; clkt->div; clkt++)
			if (clkt->val == val)
				return clkt->div;
		if (clkt->div == 0)
			return 0;
	}
	return val + 1;
}