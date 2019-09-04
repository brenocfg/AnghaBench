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
typedef  int /*<<< orphan*/  u64 ;
typedef  int /*<<< orphan*/  u32 ;
struct clk_hw {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  regmap; } ;
struct clk_alpha_pll {TYPE_1__ clkr; } ;

/* Variables and functions */
 int EINVAL ; 
 unsigned long FABIA_PLL_RATE_MARGIN ; 
 int /*<<< orphan*/  PLL_FRAC (struct clk_alpha_pll*) ; 
 int /*<<< orphan*/  PLL_L_VAL (struct clk_alpha_pll*) ; 
 int /*<<< orphan*/  PLL_MODE (struct clk_alpha_pll*) ; 
 int __clk_alpha_pll_update_latch (struct clk_alpha_pll*) ; 
 unsigned long alpha_pll_round_rate (unsigned long,unsigned long,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pll_alpha_width (struct clk_alpha_pll*) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct clk_alpha_pll* to_clk_alpha_pll (struct clk_hw*) ; 

__attribute__((used)) static int alpha_pll_fabia_set_rate(struct clk_hw *hw, unsigned long rate,
						unsigned long prate)
{
	struct clk_alpha_pll *pll = to_clk_alpha_pll(hw);
	u32 val, l, alpha_width = pll_alpha_width(pll);
	u64 a;
	unsigned long rrate;
	int ret = 0;

	ret = regmap_read(pll->clkr.regmap, PLL_MODE(pll), &val);
	if (ret)
		return ret;

	rrate = alpha_pll_round_rate(rate, prate, &l, &a, alpha_width);

	/*
	 * Due to limited number of bits for fractional rate programming, the
	 * rounded up rate could be marginally higher than the requested rate.
	 */
	if (rrate > (rate + FABIA_PLL_RATE_MARGIN) || rrate < rate) {
		pr_err("Call set rate on the PLL with rounded rates!\n");
		return -EINVAL;
	}

	regmap_write(pll->clkr.regmap, PLL_L_VAL(pll), l);
	regmap_write(pll->clkr.regmap, PLL_FRAC(pll), a);

	return __clk_alpha_pll_update_latch(pll);
}