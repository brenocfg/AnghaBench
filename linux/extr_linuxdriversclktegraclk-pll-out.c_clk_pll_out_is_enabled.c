#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int u32 ;
struct tegra_clk_pll_out {int /*<<< orphan*/  reg; } ;
struct clk_hw {int dummy; } ;

/* Variables and functions */
 int pll_out_enb (struct tegra_clk_pll_out*) ; 
 int pll_out_rst (struct tegra_clk_pll_out*) ; 
 int readl_relaxed (int /*<<< orphan*/ ) ; 
 struct tegra_clk_pll_out* to_clk_pll_out (struct clk_hw*) ; 

__attribute__((used)) static int clk_pll_out_is_enabled(struct clk_hw *hw)
{
	struct tegra_clk_pll_out *pll_out = to_clk_pll_out(hw);
	u32 val = readl_relaxed(pll_out->reg);
	int state;

	state = (val & pll_out_enb(pll_out)) ? 1 : 0;
	if (!(val & (pll_out_rst(pll_out))))
		state = 0;
	return state;
}