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
struct TYPE_2__ {int /*<<< orphan*/  regmap; } ;
struct clk_pll {int /*<<< orphan*/  mode_reg; TYPE_1__ clkr; } ;
struct clk_hw {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  PLL_BYPASSNL ; 
 int /*<<< orphan*/  PLL_OUTCTRL ; 
 int /*<<< orphan*/  PLL_RESET_N ; 
 int regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct clk_pll* to_clk_pll (struct clk_hw*) ; 
 int /*<<< orphan*/  udelay (int) ; 
 int wait_for_pll (struct clk_pll*) ; 

__attribute__((used)) static int clk_pll_sr2_enable(struct clk_hw *hw)
{
	struct clk_pll *pll = to_clk_pll(hw);
	int ret;
	u32 mode;

	ret = regmap_read(pll->clkr.regmap, pll->mode_reg, &mode);
	if (ret)
		return ret;

	/* Disable PLL bypass mode. */
	ret = regmap_update_bits(pll->clkr.regmap, pll->mode_reg, PLL_BYPASSNL,
				 PLL_BYPASSNL);
	if (ret)
		return ret;

	/*
	 * H/W requires a 5us delay between disabling the bypass and
	 * de-asserting the reset. Delay 10us just to be safe.
	 */
	udelay(10);

	/* De-assert active-low PLL reset. */
	ret = regmap_update_bits(pll->clkr.regmap, pll->mode_reg, PLL_RESET_N,
				 PLL_RESET_N);
	if (ret)
		return ret;

	ret = wait_for_pll(pll);
	if (ret)
		return ret;

	/* Enable PLL output. */
	return regmap_update_bits(pll->clkr.regmap, pll->mode_reg, PLL_OUTCTRL,
				 PLL_OUTCTRL);
}