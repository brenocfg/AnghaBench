#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u32 ;
struct TYPE_2__ {int dpll_speed; } ;

/* Variables and functions */
 scalar_t__ CORE_CLK_SRC_DPLL ; 
 TYPE_1__* curr_prcm_set ; 
 scalar_t__ omap2xxx_cm_get_core_clk_src () ; 

__attribute__((used)) static long omap2_dpllcore_round_rate(unsigned long target_rate)
{
	u32 high, low, core_clk_src;

	core_clk_src = omap2xxx_cm_get_core_clk_src();

	if (core_clk_src == CORE_CLK_SRC_DPLL) {	/* DPLL clockout */
		high = curr_prcm_set->dpll_speed * 2;
		low = curr_prcm_set->dpll_speed;
	} else {				/* DPLL clockout x 2 */
		high = curr_prcm_set->dpll_speed;
		low = curr_prcm_set->dpll_speed / 2;
	}

#ifdef DOWN_VARIABLE_DPLL
	if (target_rate > high)
		return high;
	else
		return target_rate;
#else
	if (target_rate > low)
		return high;
	else
		return low;
#endif

}