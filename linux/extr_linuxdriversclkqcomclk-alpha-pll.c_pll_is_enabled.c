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
struct clk_hw {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  regmap; } ;
struct clk_alpha_pll {TYPE_1__ clkr; } ;

/* Variables and functions */
 int /*<<< orphan*/  PLL_MODE (struct clk_alpha_pll*) ; 
 int regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 struct clk_alpha_pll* to_clk_alpha_pll (struct clk_hw*) ; 

__attribute__((used)) static int pll_is_enabled(struct clk_hw *hw, u32 mask)
{
	int ret;
	struct clk_alpha_pll *pll = to_clk_alpha_pll(hw);
	u32 val;

	ret = regmap_read(pll->clkr.regmap, PLL_MODE(pll), &val);
	if (ret)
		return ret;

	return !!(val & mask);
}