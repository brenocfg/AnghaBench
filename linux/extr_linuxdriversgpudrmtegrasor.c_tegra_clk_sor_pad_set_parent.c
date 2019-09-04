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
typedef  int u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct tegra_sor {int dummy; } ;
struct tegra_clk_sor_pad {struct tegra_sor* sor; } ;
struct clk_hw {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SOR_CLK_CNTRL ; 
 int /*<<< orphan*/  SOR_CLK_CNTRL_DP_CLK_SEL_MASK ; 
 int /*<<< orphan*/  SOR_CLK_CNTRL_DP_CLK_SEL_SINGLE_DPCLK ; 
 int /*<<< orphan*/  SOR_CLK_CNTRL_DP_CLK_SEL_SINGLE_PCLK ; 
 int /*<<< orphan*/  tegra_sor_readl (struct tegra_sor*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tegra_sor_writel (struct tegra_sor*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct tegra_clk_sor_pad* to_pad (struct clk_hw*) ; 

__attribute__((used)) static int tegra_clk_sor_pad_set_parent(struct clk_hw *hw, u8 index)
{
	struct tegra_clk_sor_pad *pad = to_pad(hw);
	struct tegra_sor *sor = pad->sor;
	u32 value;

	value = tegra_sor_readl(sor, SOR_CLK_CNTRL);
	value &= ~SOR_CLK_CNTRL_DP_CLK_SEL_MASK;

	switch (index) {
	case 0:
		value |= SOR_CLK_CNTRL_DP_CLK_SEL_SINGLE_PCLK;
		break;

	case 1:
		value |= SOR_CLK_CNTRL_DP_CLK_SEL_SINGLE_DPCLK;
		break;
	}

	tegra_sor_writel(sor, value, SOR_CLK_CNTRL);

	return 0;
}