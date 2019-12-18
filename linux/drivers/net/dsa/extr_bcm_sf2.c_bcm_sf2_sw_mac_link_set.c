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
typedef  int /*<<< orphan*/  u32 ;
struct dsa_switch {int dummy; } ;
struct bcm_sf2_priv {int dummy; } ;
typedef  scalar_t__ phy_interface_t ;

/* Variables and functions */
 scalar_t__ PHY_INTERFACE_MODE_MII ; 
 scalar_t__ PHY_INTERFACE_MODE_REVMII ; 
 int /*<<< orphan*/  REG_RGMII_CNTRL_P (int) ; 
 int /*<<< orphan*/  RGMII_MODE_EN ; 
 struct bcm_sf2_priv* bcm_sf2_to_priv (struct dsa_switch*) ; 
 int /*<<< orphan*/  phy_interface_mode_is_rgmii (scalar_t__) ; 
 int /*<<< orphan*/  reg_readl (struct bcm_sf2_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reg_writel (struct bcm_sf2_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void bcm_sf2_sw_mac_link_set(struct dsa_switch *ds, int port,
				    phy_interface_t interface, bool link)
{
	struct bcm_sf2_priv *priv = bcm_sf2_to_priv(ds);
	u32 reg;

	if (!phy_interface_mode_is_rgmii(interface) &&
	    interface != PHY_INTERFACE_MODE_MII &&
	    interface != PHY_INTERFACE_MODE_REVMII)
		return;

	/* If the link is down, just disable the interface to conserve power */
	reg = reg_readl(priv, REG_RGMII_CNTRL_P(port));
	if (link)
		reg |= RGMII_MODE_EN;
	else
		reg &= ~RGMII_MODE_EN;
	reg_writel(priv, reg, REG_RGMII_CNTRL_P(port));
}