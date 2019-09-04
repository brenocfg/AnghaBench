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
struct TYPE_2__ {int /*<<< orphan*/  regmap; } ;
struct clk_pll {int /*<<< orphan*/  mode_reg; TYPE_1__ clkr; } ;
struct clk_hw {int dummy; } ;

/* Variables and functions */
 int PLL_BYPASSNL ; 
 int PLL_OUTCTRL ; 
 int PLL_RESET_N ; 
 int PLL_VOTE_FSM_ENA ; 
 int /*<<< orphan*/  regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 struct clk_pll* to_clk_pll (struct clk_hw*) ; 

__attribute__((used)) static void clk_pll_disable(struct clk_hw *hw)
{
	struct clk_pll *pll = to_clk_pll(hw);
	u32 mask;
	u32 val;

	regmap_read(pll->clkr.regmap, pll->mode_reg, &val);
	/* Skip if in FSM mode */
	if (val & PLL_VOTE_FSM_ENA)
		return;
	mask = PLL_OUTCTRL | PLL_RESET_N | PLL_BYPASSNL;
	regmap_update_bits(pll->clkr.regmap, pll->mode_reg, mask, 0);
}