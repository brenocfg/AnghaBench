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
typedef  int /*<<< orphan*/  u32 ;
struct clk_hw {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  regmap; } ;
struct clk_alpha_pll {TYPE_1__ clkr; } ;

/* Variables and functions */
 int /*<<< orphan*/  PLL_FRAC (struct clk_alpha_pll*) ; 
 int /*<<< orphan*/  PLL_L_VAL (struct clk_alpha_pll*) ; 
 unsigned long alpha_pll_calc_rate (unsigned long,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pll_alpha_width (struct clk_alpha_pll*) ; 
 int /*<<< orphan*/  regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct clk_alpha_pll* to_clk_alpha_pll (struct clk_hw*) ; 

__attribute__((used)) static unsigned long alpha_pll_fabia_recalc_rate(struct clk_hw *hw,
						unsigned long parent_rate)
{
	struct clk_alpha_pll *pll = to_clk_alpha_pll(hw);
	u32 l, frac, alpha_width = pll_alpha_width(pll);

	regmap_read(pll->clkr.regmap, PLL_L_VAL(pll), &l);
	regmap_read(pll->clkr.regmap, PLL_FRAC(pll), &frac);

	return alpha_pll_calc_rate(parent_rate, l, frac, alpha_width);
}