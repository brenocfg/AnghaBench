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
struct clockdomain {int dummy; } ;
struct clk_hw_omap {int /*<<< orphan*/  clkdm_name; struct clockdomain* clkdm; } ;
struct clk_hw {int /*<<< orphan*/  clk; } ;
struct TYPE_2__ {struct clockdomain* (* clkdm_lookup ) (int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 char* __clk_get_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_debug (char*,char const*,int /*<<< orphan*/ ) ; 
 struct clockdomain* stub1 (int /*<<< orphan*/ ) ; 
 TYPE_1__* ti_clk_ll_ops ; 
 struct clk_hw_omap* to_clk_hw_omap (struct clk_hw*) ; 

void omap2_init_clk_clkdm(struct clk_hw *hw)
{
	struct clk_hw_omap *clk = to_clk_hw_omap(hw);
	struct clockdomain *clkdm;
	const char *clk_name;

	if (!clk->clkdm_name)
		return;

	clk_name = __clk_get_name(hw->clk);

	clkdm = ti_clk_ll_ops->clkdm_lookup(clk->clkdm_name);
	if (clkdm) {
		pr_debug("clock: associated clk %s to clkdm %s\n",
			 clk_name, clk->clkdm_name);
		clk->clkdm = clkdm;
	} else {
		pr_debug("clock: could not associate clk %s to clkdm %s\n",
			 clk_name, clk->clkdm_name);
	}
}