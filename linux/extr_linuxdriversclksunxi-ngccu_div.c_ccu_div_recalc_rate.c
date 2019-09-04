#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  unsigned long u32 ;
struct clk_hw {int dummy; } ;
struct TYPE_4__ {int features; scalar_t__ reg; scalar_t__ base; } ;
struct TYPE_3__ {unsigned long shift; int width; int /*<<< orphan*/  flags; int /*<<< orphan*/  table; } ;
struct ccu_div {unsigned long fixed_post_div; TYPE_2__ common; TYPE_1__ div; int /*<<< orphan*/  mux; } ;

/* Variables and functions */
 int CCU_FEATURE_FIXED_POSTDIV ; 
 unsigned long ccu_mux_helper_apply_prediv (TYPE_2__*,int /*<<< orphan*/ *,int,unsigned long) ; 
 unsigned long divider_recalc_rate (struct clk_hw*,unsigned long,unsigned long,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 struct ccu_div* hw_to_ccu_div (struct clk_hw*) ; 
 unsigned long readl (scalar_t__) ; 

__attribute__((used)) static unsigned long ccu_div_recalc_rate(struct clk_hw *hw,
					unsigned long parent_rate)
{
	struct ccu_div *cd = hw_to_ccu_div(hw);
	unsigned long val;
	u32 reg;

	reg = readl(cd->common.base + cd->common.reg);
	val = reg >> cd->div.shift;
	val &= (1 << cd->div.width) - 1;

	parent_rate = ccu_mux_helper_apply_prediv(&cd->common, &cd->mux, -1,
						  parent_rate);

	val = divider_recalc_rate(hw, parent_rate, val, cd->div.table,
				  cd->div.flags, cd->div.width);

	if (cd->common.features & CCU_FEATURE_FIXED_POSTDIV)
		val /= cd->fixed_post_div;

	return val;
}