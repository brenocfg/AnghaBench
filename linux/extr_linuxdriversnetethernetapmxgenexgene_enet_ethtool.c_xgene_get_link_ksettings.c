#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct xgene_enet_pdata {scalar_t__ phy_mode; scalar_t__ mdio_driver; } ;
struct phy_device {int dummy; } ;
struct net_device {struct phy_device* phydev; } ;
struct TYPE_4__ {int /*<<< orphan*/  autoneg; int /*<<< orphan*/  port; void* duplex; int /*<<< orphan*/  speed; } ;
struct TYPE_3__ {int /*<<< orphan*/  advertising; int /*<<< orphan*/  supported; } ;
struct ethtool_link_ksettings {TYPE_2__ base; TYPE_1__ link_modes; } ;

/* Variables and functions */
 int /*<<< orphan*/  AUTONEG_DISABLE ; 
 int /*<<< orphan*/  AUTONEG_ENABLE ; 
 void* DUPLEX_FULL ; 
 int ENODEV ; 
 scalar_t__ PHY_INTERFACE_MODE_SGMII ; 
 int /*<<< orphan*/  PORT_FIBRE ; 
 int /*<<< orphan*/  PORT_MII ; 
 int /*<<< orphan*/  SPEED_1000 ; 
 int /*<<< orphan*/  SPEED_10000 ; 
 int SUPPORTED_10000baseT_Full ; 
 int SUPPORTED_1000baseT_Full ; 
 int SUPPORTED_Autoneg ; 
 int SUPPORTED_FIBRE ; 
 int SUPPORTED_MII ; 
 int /*<<< orphan*/  ethtool_convert_legacy_u32_to_link_mode (int /*<<< orphan*/ ,int) ; 
 struct xgene_enet_pdata* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  phy_ethtool_ksettings_get (struct phy_device*,struct ethtool_link_ksettings*) ; 
 scalar_t__ phy_interface_mode_is_rgmii (scalar_t__) ; 

__attribute__((used)) static int xgene_get_link_ksettings(struct net_device *ndev,
				    struct ethtool_link_ksettings *cmd)
{
	struct xgene_enet_pdata *pdata = netdev_priv(ndev);
	struct phy_device *phydev = ndev->phydev;
	u32 supported;

	if (phy_interface_mode_is_rgmii(pdata->phy_mode)) {
		if (phydev == NULL)
			return -ENODEV;

		phy_ethtool_ksettings_get(phydev, cmd);

		return 0;
	} else if (pdata->phy_mode == PHY_INTERFACE_MODE_SGMII) {
		if (pdata->mdio_driver) {
			if (!phydev)
				return -ENODEV;

			phy_ethtool_ksettings_get(phydev, cmd);

			return 0;
		}

		supported = SUPPORTED_1000baseT_Full | SUPPORTED_Autoneg |
			SUPPORTED_MII;
		ethtool_convert_legacy_u32_to_link_mode(
			cmd->link_modes.supported,
			supported);
		ethtool_convert_legacy_u32_to_link_mode(
			cmd->link_modes.advertising,
			supported);

		cmd->base.speed = SPEED_1000;
		cmd->base.duplex = DUPLEX_FULL;
		cmd->base.port = PORT_MII;
		cmd->base.autoneg = AUTONEG_ENABLE;
	} else {
		supported = SUPPORTED_10000baseT_Full | SUPPORTED_FIBRE;
		ethtool_convert_legacy_u32_to_link_mode(
			cmd->link_modes.supported,
			supported);
		ethtool_convert_legacy_u32_to_link_mode(
			cmd->link_modes.advertising,
			supported);

		cmd->base.speed = SPEED_10000;
		cmd->base.duplex = DUPLEX_FULL;
		cmd->base.port = PORT_FIBRE;
		cmd->base.autoneg = AUTONEG_DISABLE;
	}

	return 0;
}