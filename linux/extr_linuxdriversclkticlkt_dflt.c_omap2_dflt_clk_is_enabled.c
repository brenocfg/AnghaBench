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
typedef  int u32 ;
struct clk_hw_omap {int flags; int /*<<< orphan*/  enable_bit; int /*<<< orphan*/  enable_reg; } ;
struct clk_hw {int dummy; } ;
struct TYPE_2__ {int (* clk_readl ) (int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 int BIT (int /*<<< orphan*/ ) ; 
 int INVERT_ENABLE ; 
 int stub1 (int /*<<< orphan*/ *) ; 
 TYPE_1__* ti_clk_ll_ops ; 
 struct clk_hw_omap* to_clk_hw_omap (struct clk_hw*) ; 

int omap2_dflt_clk_is_enabled(struct clk_hw *hw)
{
	struct clk_hw_omap *clk = to_clk_hw_omap(hw);
	u32 v;

	v = ti_clk_ll_ops->clk_readl(&clk->enable_reg);

	if (clk->flags & INVERT_ENABLE)
		v ^= BIT(clk->enable_bit);

	v &= BIT(clk->enable_bit);

	return v ? 1 : 0;
}