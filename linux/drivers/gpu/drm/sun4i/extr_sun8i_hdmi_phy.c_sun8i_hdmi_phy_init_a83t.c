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
struct sun8i_hdmi_phy {int /*<<< orphan*/  regs; } ;

/* Variables and functions */
 int /*<<< orphan*/  I2C_ADDR ; 
 int /*<<< orphan*/  SUN8I_HDMI_PHY_DBG_CTRL_ADDR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SUN8I_HDMI_PHY_DBG_CTRL_ADDR_MASK ; 
 int /*<<< orphan*/  SUN8I_HDMI_PHY_DBG_CTRL_PX_LOCK ; 
 int /*<<< orphan*/  SUN8I_HDMI_PHY_DBG_CTRL_REG ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sun8i_hdmi_phy_unlock (struct sun8i_hdmi_phy*) ; 

__attribute__((used)) static void sun8i_hdmi_phy_init_a83t(struct sun8i_hdmi_phy *phy)
{
	sun8i_hdmi_phy_unlock(phy);

	regmap_update_bits(phy->regs, SUN8I_HDMI_PHY_DBG_CTRL_REG,
			   SUN8I_HDMI_PHY_DBG_CTRL_PX_LOCK,
			   SUN8I_HDMI_PHY_DBG_CTRL_PX_LOCK);

	/*
	 * Set PHY I2C address. It must match to the address set by
	 * dw_hdmi_phy_set_slave_addr().
	 */
	regmap_update_bits(phy->regs, SUN8I_HDMI_PHY_DBG_CTRL_REG,
			   SUN8I_HDMI_PHY_DBG_CTRL_ADDR_MASK,
			   SUN8I_HDMI_PHY_DBG_CTRL_ADDR(I2C_ADDR));
}