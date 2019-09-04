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
typedef  int u64 ;
typedef  int u32 ;
struct pll_vco {int val; } ;
struct clk_hw {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  regmap; } ;
struct clk_alpha_pll {TYPE_1__ clkr; scalar_t__ vco_table; } ;

/* Variables and functions */
 int ALPHA_BITWIDTH ; 
 int EINVAL ; 
 int PLL_ALPHA_EN ; 
 int /*<<< orphan*/  PLL_ALPHA_VAL (struct clk_alpha_pll*) ; 
 int /*<<< orphan*/  PLL_ALPHA_VAL_U (struct clk_alpha_pll*) ; 
 int /*<<< orphan*/  PLL_L_VAL (struct clk_alpha_pll*) ; 
 int /*<<< orphan*/  PLL_USER_CTL (struct clk_alpha_pll*) ; 
 int PLL_VCO_MASK ; 
 int PLL_VCO_SHIFT ; 
 struct pll_vco* alpha_pll_find_vco (struct clk_alpha_pll*,unsigned long) ; 
 unsigned long alpha_pll_round_rate (unsigned long,unsigned long,int*,int*,int) ; 
 int clk_alpha_pll_update_latch (struct clk_alpha_pll*,int (*) (struct clk_hw*)) ; 
 int pll_alpha_width (struct clk_alpha_pll*) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 struct clk_alpha_pll* to_clk_alpha_pll (struct clk_hw*) ; 

__attribute__((used)) static int __clk_alpha_pll_set_rate(struct clk_hw *hw, unsigned long rate,
				    unsigned long prate,
				    int (*is_enabled)(struct clk_hw *))
{
	struct clk_alpha_pll *pll = to_clk_alpha_pll(hw);
	const struct pll_vco *vco;
	u32 l, alpha_width = pll_alpha_width(pll);
	u64 a;

	rate = alpha_pll_round_rate(rate, prate, &l, &a, alpha_width);
	vco = alpha_pll_find_vco(pll, rate);
	if (pll->vco_table && !vco) {
		pr_err("alpha pll not in a valid vco range\n");
		return -EINVAL;
	}

	regmap_write(pll->clkr.regmap, PLL_L_VAL(pll), l);

	if (alpha_width > ALPHA_BITWIDTH)
		a <<= alpha_width - ALPHA_BITWIDTH;

	if (alpha_width > 32)
		regmap_write(pll->clkr.regmap, PLL_ALPHA_VAL_U(pll), a >> 32);

	regmap_write(pll->clkr.regmap, PLL_ALPHA_VAL(pll), a);

	if (vco) {
		regmap_update_bits(pll->clkr.regmap, PLL_USER_CTL(pll),
				   PLL_VCO_MASK << PLL_VCO_SHIFT,
				   vco->val << PLL_VCO_SHIFT);
	}

	regmap_update_bits(pll->clkr.regmap, PLL_USER_CTL(pll),
			   PLL_ALPHA_EN, PLL_ALPHA_EN);

	return clk_alpha_pll_update_latch(pll, is_enabled);
}