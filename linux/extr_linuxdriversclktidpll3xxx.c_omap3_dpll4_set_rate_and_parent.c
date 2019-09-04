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
typedef  int /*<<< orphan*/  u8 ;
struct clk_hw {int dummy; } ;
struct TYPE_2__ {int flags; } ;

/* Variables and functions */
 int EINVAL ; 
 int TI_CLK_DPLL4_DENY_REPROGRAM ; 
 int omap3_noncore_dpll_set_rate_and_parent (struct clk_hw*,unsigned long,unsigned long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 TYPE_1__* ti_clk_get_features () ; 

int omap3_dpll4_set_rate_and_parent(struct clk_hw *hw, unsigned long rate,
				    unsigned long parent_rate, u8 index)
{
	if (ti_clk_get_features()->flags & TI_CLK_DPLL4_DENY_REPROGRAM) {
		pr_err("clock: DPLL4 cannot change rate due to silicon 'Limitation 2.5' on 3430ES1.\n");
		return -EINVAL;
	}

	return omap3_noncore_dpll_set_rate_and_parent(hw, rate, parent_rate,
						      index);
}