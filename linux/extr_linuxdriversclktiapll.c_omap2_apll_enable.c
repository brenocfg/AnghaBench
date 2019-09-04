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
struct dpll_data {int enable_mask; int idlest_mask; int /*<<< orphan*/  idlest_reg; int /*<<< orphan*/  control_reg; } ;
struct clk_hw_omap {int /*<<< orphan*/  hw; struct dpll_data* dpll_data; } ;
struct clk_hw {int dummy; } ;
struct TYPE_2__ {int (* clk_readl ) (int /*<<< orphan*/ *) ;int /*<<< orphan*/  (* clk_writel ) (int,int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 int EBUSY ; 
 int MAX_APLL_WAIT_TRIES ; 
 int OMAP2_EN_APLL_LOCKED ; 
 int __ffs (int) ; 
 int /*<<< orphan*/  clk_hw_get_name (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_warn (char*,int /*<<< orphan*/ ) ; 
 int stub1 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub2 (int,int /*<<< orphan*/ *) ; 
 int stub3 (int /*<<< orphan*/ *) ; 
 TYPE_1__* ti_clk_ll_ops ; 
 struct clk_hw_omap* to_clk_hw_omap (struct clk_hw*) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static int omap2_apll_enable(struct clk_hw *hw)
{
	struct clk_hw_omap *clk = to_clk_hw_omap(hw);
	struct dpll_data *ad = clk->dpll_data;
	u32 v;
	int i = 0;

	v = ti_clk_ll_ops->clk_readl(&ad->control_reg);
	v &= ~ad->enable_mask;
	v |= OMAP2_EN_APLL_LOCKED << __ffs(ad->enable_mask);
	ti_clk_ll_ops->clk_writel(v, &ad->control_reg);

	while (1) {
		v = ti_clk_ll_ops->clk_readl(&ad->idlest_reg);
		if (v & ad->idlest_mask)
			break;
		if (i > MAX_APLL_WAIT_TRIES)
			break;
		i++;
		udelay(1);
	}

	if (i == MAX_APLL_WAIT_TRIES) {
		pr_warn("%s failed to transition to locked\n",
			clk_hw_get_name(&clk->hw));
		return -EBUSY;
	}

	return 0;
}