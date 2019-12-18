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
struct sun8i_phy_clk {TYPE_1__* phy; } ;
struct clk_hw {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  regs; } ;

/* Variables and functions */
 int SUN8I_HDMI_PHY_PLL_CFG2_PREDIV_MSK ; 
 int SUN8I_HDMI_PHY_PLL_CFG2_PREDIV_SHIFT ; 
 int /*<<< orphan*/  SUN8I_HDMI_PHY_PLL_CFG2_REG ; 
 struct sun8i_phy_clk* hw_to_phy_clk (struct clk_hw*) ; 
 int /*<<< orphan*/  regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static unsigned long sun8i_phy_clk_recalc_rate(struct clk_hw *hw,
					       unsigned long parent_rate)
{
	struct sun8i_phy_clk *priv = hw_to_phy_clk(hw);
	u32 reg;

	regmap_read(priv->phy->regs, SUN8I_HDMI_PHY_PLL_CFG2_REG, &reg);
	reg = ((reg >> SUN8I_HDMI_PHY_PLL_CFG2_PREDIV_SHIFT) &
		SUN8I_HDMI_PHY_PLL_CFG2_PREDIV_MSK) + 1;

	return parent_rate / reg;
}