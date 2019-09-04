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
struct dw_hdmi {int dummy; } ;

/* Variables and functions */
 int SUN8I_HDMI_PHY_ANA_CFG1_ENBI ; 
 int SUN8I_HDMI_PHY_ANA_CFG1_ENVBS ; 
 int SUN8I_HDMI_PHY_ANA_CFG1_LDOEN ; 
 int /*<<< orphan*/  SUN8I_HDMI_PHY_ANA_CFG1_REG ; 
 int /*<<< orphan*/  SUN8I_HDMI_PHY_PLL_CFG1_REG ; 
 int /*<<< orphan*/  regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void sun8i_hdmi_phy_disable_h3(struct dw_hdmi *hdmi,
				      struct sun8i_hdmi_phy *phy)
{
	regmap_write(phy->regs, SUN8I_HDMI_PHY_ANA_CFG1_REG,
		     SUN8I_HDMI_PHY_ANA_CFG1_LDOEN |
		     SUN8I_HDMI_PHY_ANA_CFG1_ENVBS |
		     SUN8I_HDMI_PHY_ANA_CFG1_ENBI);
	regmap_write(phy->regs, SUN8I_HDMI_PHY_PLL_CFG1_REG, 0);
}