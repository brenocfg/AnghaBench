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
typedef  int u32 ;
struct tegra_sor {int dummy; } ;
struct tegra_clk_sor_pad {struct tegra_sor* sor; } ;
struct clk_hw {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SOR_CLK_CNTRL ; 
#define  SOR_CLK_CNTRL_DP_CLK_SEL_DIFF_DPCLK 131 
#define  SOR_CLK_CNTRL_DP_CLK_SEL_DIFF_PCLK 130 
 int SOR_CLK_CNTRL_DP_CLK_SEL_MASK ; 
#define  SOR_CLK_CNTRL_DP_CLK_SEL_SINGLE_DPCLK 129 
#define  SOR_CLK_CNTRL_DP_CLK_SEL_SINGLE_PCLK 128 
 int U8_MAX ; 
 int tegra_sor_readl (struct tegra_sor*,int /*<<< orphan*/ ) ; 
 struct tegra_clk_sor_pad* to_pad (struct clk_hw*) ; 

__attribute__((used)) static u8 tegra_clk_sor_pad_get_parent(struct clk_hw *hw)
{
	struct tegra_clk_sor_pad *pad = to_pad(hw);
	struct tegra_sor *sor = pad->sor;
	u8 parent = U8_MAX;
	u32 value;

	value = tegra_sor_readl(sor, SOR_CLK_CNTRL);

	switch (value & SOR_CLK_CNTRL_DP_CLK_SEL_MASK) {
	case SOR_CLK_CNTRL_DP_CLK_SEL_SINGLE_PCLK:
	case SOR_CLK_CNTRL_DP_CLK_SEL_DIFF_PCLK:
		parent = 0;
		break;

	case SOR_CLK_CNTRL_DP_CLK_SEL_SINGLE_DPCLK:
	case SOR_CLK_CNTRL_DP_CLK_SEL_DIFF_DPCLK:
		parent = 1;
		break;
	}

	return parent;
}