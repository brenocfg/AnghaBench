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
struct TYPE_4__ {int duplex; scalar_t__ autoneg; scalar_t__ speed; int /*<<< orphan*/  phy_address; scalar_t__ port; } ;
struct TYPE_3__ {int /*<<< orphan*/  advertising; int /*<<< orphan*/  supported; } ;
struct ethtool_link_ksettings {TYPE_2__ base; TYPE_1__ link_modes; } ;
struct b44 {int flags; int /*<<< orphan*/  phy_addr; } ;

/* Variables and functions */
 int ADVERTISED_100baseT_Full ; 
 int ADVERTISED_100baseT_Half ; 
 int ADVERTISED_10baseT_Full ; 
 int ADVERTISED_10baseT_Half ; 
 int ADVERTISED_Asym_Pause ; 
 int ADVERTISED_Autoneg ; 
 int ADVERTISED_Pause ; 
 scalar_t__ AUTONEG_DISABLE ; 
 scalar_t__ AUTONEG_ENABLE ; 
 int B44_FLAG_100_BASE_T ; 
 int B44_FLAG_ADV_100FULL ; 
 int B44_FLAG_ADV_100HALF ; 
 int B44_FLAG_ADV_10FULL ; 
 int B44_FLAG_ADV_10HALF ; 
 int B44_FLAG_EXTERNAL_PHY ; 
 int B44_FLAG_FORCE_LINK ; 
 int B44_FLAG_FULL_DUPLEX ; 
 int /*<<< orphan*/  BUG_ON (int) ; 
 int DUPLEX_FULL ; 
 int DUPLEX_HALF ; 
 scalar_t__ SPEED_10 ; 
 scalar_t__ SPEED_100 ; 
 int SUPPORTED_100baseT_Full ; 
 int SUPPORTED_100baseT_Half ; 
 int SUPPORTED_10baseT_Full ; 
 int SUPPORTED_10baseT_Half ; 
 int SUPPORTED_Autoneg ; 
 int SUPPORTED_MII ; 
 int /*<<< orphan*/  ethtool_convert_legacy_u32_to_link_mode (int /*<<< orphan*/ ,int) ; 
 struct b44* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_running (struct net_device*) ; 
 int /*<<< orphan*/  phy_ethtool_ksettings_get (int /*<<< orphan*/ ,struct ethtool_link_ksettings*) ; 

__attribute__((used)) static int b44_get_link_ksettings(struct net_device *dev,
				  struct ethtool_link_ksettings *cmd)
{
	struct b44 *bp = netdev_priv(dev);
	u32 supported, advertising;

	if (bp->flags & B44_FLAG_EXTERNAL_PHY) {
		BUG_ON(!dev->phydev);
		phy_ethtool_ksettings_get(dev->phydev, cmd);

		return 0;
	}

	supported = (SUPPORTED_Autoneg);
	supported |= (SUPPORTED_100baseT_Half |
		      SUPPORTED_100baseT_Full |
		      SUPPORTED_10baseT_Half |
		      SUPPORTED_10baseT_Full |
		      SUPPORTED_MII);

	advertising = 0;
	if (bp->flags & B44_FLAG_ADV_10HALF)
		advertising |= ADVERTISED_10baseT_Half;
	if (bp->flags & B44_FLAG_ADV_10FULL)
		advertising |= ADVERTISED_10baseT_Full;
	if (bp->flags & B44_FLAG_ADV_100HALF)
		advertising |= ADVERTISED_100baseT_Half;
	if (bp->flags & B44_FLAG_ADV_100FULL)
		advertising |= ADVERTISED_100baseT_Full;
	advertising |= ADVERTISED_Pause | ADVERTISED_Asym_Pause;
	cmd->base.speed = (bp->flags & B44_FLAG_100_BASE_T) ?
		SPEED_100 : SPEED_10;
	cmd->base.duplex = (bp->flags & B44_FLAG_FULL_DUPLEX) ?
		DUPLEX_FULL : DUPLEX_HALF;
	cmd->base.port = 0;
	cmd->base.phy_address = bp->phy_addr;
	cmd->base.autoneg = (bp->flags & B44_FLAG_FORCE_LINK) ?
		AUTONEG_DISABLE : AUTONEG_ENABLE;
	if (cmd->base.autoneg == AUTONEG_ENABLE)
		advertising |= ADVERTISED_Autoneg;

	ethtool_convert_legacy_u32_to_link_mode(cmd->link_modes.supported,
						supported);
	ethtool_convert_legacy_u32_to_link_mode(cmd->link_modes.advertising,
						advertising);

	if (!netif_running(dev)){
		cmd->base.speed = 0;
		cmd->base.duplex = 0xff;
	}

	return 0;
}