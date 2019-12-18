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
typedef  int u8 ;
struct sun8i_phy_clk {TYPE_1__* phy; } ;
struct clk_hw {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  regs; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  SUN8I_HDMI_PHY_PLL_CFG1_CKIN_SEL_MSK ; 
 int SUN8I_HDMI_PHY_PLL_CFG1_CKIN_SEL_SHIFT ; 
 int /*<<< orphan*/  SUN8I_HDMI_PHY_PLL_CFG1_REG ; 
 struct sun8i_phy_clk* hw_to_phy_clk (struct clk_hw*) ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int sun8i_phy_clk_set_parent(struct clk_hw *hw, u8 index)
{
	struct sun8i_phy_clk *priv = hw_to_phy_clk(hw);

	if (index > 1)
		return -EINVAL;

	regmap_update_bits(priv->phy->regs, SUN8I_HDMI_PHY_PLL_CFG1_REG,
			   SUN8I_HDMI_PHY_PLL_CFG1_CKIN_SEL_MSK,
			   index << SUN8I_HDMI_PHY_PLL_CFG1_CKIN_SEL_SHIFT);

	return 0;
}