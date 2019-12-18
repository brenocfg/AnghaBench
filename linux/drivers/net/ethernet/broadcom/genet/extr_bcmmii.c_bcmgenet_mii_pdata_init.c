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
struct unimac_mdio_pdata {int phy_mask; } ;
struct device {struct bcmgenet_platform_data* platform_data; } ;
struct bcmgenet_priv {TYPE_1__* pdev; } ;
struct bcmgenet_platform_data {scalar_t__ phy_interface; int phy_address; scalar_t__ mdio_enabled; } ;
struct TYPE_2__ {struct device dev; } ;

/* Variables and functions */
 scalar_t__ PHY_INTERFACE_MODE_MOCA ; 
 int PHY_MAX_ADDR ; 

__attribute__((used)) static void bcmgenet_mii_pdata_init(struct bcmgenet_priv *priv,
				    struct unimac_mdio_pdata *ppd)
{
	struct device *kdev = &priv->pdev->dev;
	struct bcmgenet_platform_data *pd = kdev->platform_data;

	if (pd->phy_interface != PHY_INTERFACE_MODE_MOCA && pd->mdio_enabled) {
		/*
		 * Internal or external PHY with MDIO access
		 */
		if (pd->phy_address >= 0 && pd->phy_address < PHY_MAX_ADDR)
			ppd->phy_mask = 1 << pd->phy_address;
		else
			ppd->phy_mask = 0;
	}
}