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
struct net_device {int /*<<< orphan*/  phydev; } ;
struct TYPE_4__ {int /*<<< orphan*/  port; int /*<<< orphan*/  duplex; int /*<<< orphan*/  speed; scalar_t__ autoneg; } ;
struct TYPE_3__ {int /*<<< orphan*/  advertising; int /*<<< orphan*/  supported; } ;
struct ethtool_link_ksettings {TYPE_2__ base; TYPE_1__ link_modes; } ;
struct bcm_enet_priv {scalar_t__ force_duplex_full; scalar_t__ force_speed_100; scalar_t__ has_phy; } ;

/* Variables and functions */
 int ADVERTISED_100baseT_Full ; 
 int ADVERTISED_100baseT_Half ; 
 int ADVERTISED_10baseT_Full ; 
 int ADVERTISED_10baseT_Half ; 
 int /*<<< orphan*/  DUPLEX_FULL ; 
 int /*<<< orphan*/  DUPLEX_HALF ; 
 int ENODEV ; 
 int /*<<< orphan*/  PORT_MII ; 
 int /*<<< orphan*/  SPEED_10 ; 
 int /*<<< orphan*/  SPEED_100 ; 
 int /*<<< orphan*/  ethtool_convert_legacy_u32_to_link_mode (int /*<<< orphan*/ ,int) ; 
 struct bcm_enet_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  phy_ethtool_ksettings_get (int /*<<< orphan*/ ,struct ethtool_link_ksettings*) ; 

__attribute__((used)) static int bcm_enet_get_link_ksettings(struct net_device *dev,
				       struct ethtool_link_ksettings *cmd)
{
	struct bcm_enet_priv *priv;
	u32 supported, advertising;

	priv = netdev_priv(dev);

	if (priv->has_phy) {
		if (!dev->phydev)
			return -ENODEV;

		phy_ethtool_ksettings_get(dev->phydev, cmd);

		return 0;
	} else {
		cmd->base.autoneg = 0;
		cmd->base.speed = (priv->force_speed_100) ?
			SPEED_100 : SPEED_10;
		cmd->base.duplex = (priv->force_duplex_full) ?
			DUPLEX_FULL : DUPLEX_HALF;
		supported = ADVERTISED_10baseT_Half |
			ADVERTISED_10baseT_Full |
			ADVERTISED_100baseT_Half |
			ADVERTISED_100baseT_Full;
		advertising = 0;
		ethtool_convert_legacy_u32_to_link_mode(
			cmd->link_modes.supported, supported);
		ethtool_convert_legacy_u32_to_link_mode(
			cmd->link_modes.advertising, advertising);
		cmd->base.port = PORT_MII;
	}
	return 0;
}