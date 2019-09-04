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
struct clk_hw {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int omap3_noncore_dpll_set_parent (struct clk_hw*,scalar_t__) ; 
 int omap3_noncore_dpll_set_rate (struct clk_hw*,unsigned long,unsigned long) ; 

int omap3_noncore_dpll_set_rate_and_parent(struct clk_hw *hw,
					   unsigned long rate,
					   unsigned long parent_rate,
					   u8 index)
{
	int ret;

	if (!hw || !rate)
		return -EINVAL;

	/*
	 * clk-ref at index[0], in which case we only need to set rate,
	 * the parent will be changed automatically with the lock sequence.
	 * With clk-bypass case we only need to change parent.
	 */
	if (index)
		ret = omap3_noncore_dpll_set_parent(hw, index);
	else
		ret = omap3_noncore_dpll_set_rate(hw, rate, parent_rate);

	return ret;
}