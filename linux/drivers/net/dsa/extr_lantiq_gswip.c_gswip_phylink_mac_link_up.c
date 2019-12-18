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
struct phy_device {int dummy; } ;
struct gswip_priv {int dummy; } ;
struct dsa_switch {struct gswip_priv* priv; } ;
typedef  scalar_t__ phy_interface_t ;

/* Variables and functions */
 int /*<<< orphan*/  GSWIP_MII_CFG_EN ; 
 scalar_t__ PHY_INTERFACE_MODE_INTERNAL ; 
 int /*<<< orphan*/  gswip_mii_mask_cfg (struct gswip_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void gswip_phylink_mac_link_up(struct dsa_switch *ds, int port,
				      unsigned int mode,
				      phy_interface_t interface,
				      struct phy_device *phydev)
{
	struct gswip_priv *priv = ds->priv;

	/* Enable the xMII interface only for the external PHY */
	if (interface != PHY_INTERFACE_MODE_INTERNAL)
		gswip_mii_mask_cfg(priv, 0, GSWIP_MII_CFG_EN, port);
}