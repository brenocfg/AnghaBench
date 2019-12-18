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
struct xgene_enet_pdata {scalar_t__ phy_mode; scalar_t__ mdio_driver; } ;
struct phy_device {int dummy; } ;
struct net_device {struct phy_device* phydev; } ;
struct ethtool_link_ksettings {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENODEV ; 
 scalar_t__ PHY_INTERFACE_MODE_SGMII ; 
 struct xgene_enet_pdata* netdev_priv (struct net_device*) ; 
 int phy_ethtool_ksettings_set (struct phy_device*,struct ethtool_link_ksettings const*) ; 
 scalar_t__ phy_interface_mode_is_rgmii (scalar_t__) ; 

__attribute__((used)) static int xgene_set_link_ksettings(struct net_device *ndev,
				    const struct ethtool_link_ksettings *cmd)
{
	struct xgene_enet_pdata *pdata = netdev_priv(ndev);
	struct phy_device *phydev = ndev->phydev;

	if (phy_interface_mode_is_rgmii(pdata->phy_mode)) {
		if (!phydev)
			return -ENODEV;

		return phy_ethtool_ksettings_set(phydev, cmd);
	}

	if (pdata->phy_mode == PHY_INTERFACE_MODE_SGMII) {
		if (pdata->mdio_driver) {
			if (!phydev)
				return -ENODEV;

			return phy_ethtool_ksettings_set(phydev, cmd);
		}
	}

	return -EINVAL;
}