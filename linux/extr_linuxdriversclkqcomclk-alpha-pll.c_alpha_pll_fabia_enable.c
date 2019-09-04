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
struct regmap {int dummy; } ;
struct clk_hw {int dummy; } ;
struct TYPE_2__ {struct regmap* regmap; } ;
struct clk_alpha_pll {TYPE_1__ clkr; } ;

/* Variables and functions */
 int FABIA_OPMODE_RUN ; 
 int FABIA_OPMODE_STANDBY ; 
 int FABIA_PLL_OUT_MASK ; 
 int /*<<< orphan*/  PLL_MODE (struct clk_alpha_pll*) ; 
 int /*<<< orphan*/  PLL_OPMODE (struct clk_alpha_pll*) ; 
 int PLL_OUTCTRL ; 
 int PLL_RESET_N ; 
 int /*<<< orphan*/  PLL_USER_CTL (struct clk_alpha_pll*) ; 
 int PLL_VOTE_FSM_ENA ; 
 int clk_enable_regmap (struct clk_hw*) ; 
 int regmap_read (struct regmap*,int /*<<< orphan*/ ,int*) ; 
 int regmap_update_bits (struct regmap*,int /*<<< orphan*/ ,int,int) ; 
 int regmap_write (struct regmap*,int /*<<< orphan*/ ,int) ; 
 struct clk_alpha_pll* to_clk_alpha_pll (struct clk_hw*) ; 
 int wait_for_pll_enable_active (struct clk_alpha_pll*) ; 
 int wait_for_pll_enable_lock (struct clk_alpha_pll*) ; 

__attribute__((used)) static int alpha_pll_fabia_enable(struct clk_hw *hw)
{
	int ret;
	struct clk_alpha_pll *pll = to_clk_alpha_pll(hw);
	u32 val, opmode_val;
	struct regmap *regmap = pll->clkr.regmap;

	ret = regmap_read(regmap, PLL_MODE(pll), &val);
	if (ret)
		return ret;

	/* If in FSM mode, just vote for it */
	if (val & PLL_VOTE_FSM_ENA) {
		ret = clk_enable_regmap(hw);
		if (ret)
			return ret;
		return wait_for_pll_enable_active(pll);
	}

	ret = regmap_read(regmap, PLL_OPMODE(pll), &opmode_val);
	if (ret)
		return ret;

	/* Skip If PLL is already running */
	if ((opmode_val & FABIA_OPMODE_RUN) && (val & PLL_OUTCTRL))
		return 0;

	ret = regmap_update_bits(regmap, PLL_MODE(pll), PLL_OUTCTRL, 0);
	if (ret)
		return ret;

	ret = regmap_write(regmap, PLL_OPMODE(pll), FABIA_OPMODE_STANDBY);
	if (ret)
		return ret;

	ret = regmap_update_bits(regmap, PLL_MODE(pll), PLL_RESET_N,
				 PLL_RESET_N);
	if (ret)
		return ret;

	ret = regmap_write(regmap, PLL_OPMODE(pll), FABIA_OPMODE_RUN);
	if (ret)
		return ret;

	ret = wait_for_pll_enable_lock(pll);
	if (ret)
		return ret;

	ret = regmap_update_bits(regmap, PLL_USER_CTL(pll),
				 FABIA_PLL_OUT_MASK, FABIA_PLL_OUT_MASK);
	if (ret)
		return ret;

	return regmap_update_bits(regmap, PLL_MODE(pll), PLL_OUTCTRL,
				 PLL_OUTCTRL);
}