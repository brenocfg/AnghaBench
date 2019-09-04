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
struct sky2_port {int advertising; int duplex; int speed; int /*<<< orphan*/  flags; struct sky2_hw* hw; } ;
struct sky2_hw {int dummy; } ;
struct net_device {int dummy; } ;
struct TYPE_4__ {scalar_t__ autoneg; int speed; int duplex; } ;
struct TYPE_3__ {int /*<<< orphan*/  advertising; } ;
struct ethtool_link_ksettings {TYPE_2__ base; TYPE_1__ link_modes; } ;

/* Variables and functions */
 int ADVERTISED_Autoneg ; 
 int ADVERTISED_FIBRE ; 
 int ADVERTISED_TP ; 
 scalar_t__ AUTONEG_ENABLE ; 
 int DUPLEX_FULL ; 
 int DUPLEX_HALF ; 
 int EINVAL ; 
 int /*<<< orphan*/  SKY2_FLAG_AUTO_SPEED ; 
#define  SPEED_10 130 
#define  SPEED_100 129 
#define  SPEED_1000 128 
 int SUPPORTED_1000baseT_Full ; 
 int SUPPORTED_1000baseT_Half ; 
 int SUPPORTED_100baseT_Full ; 
 int SUPPORTED_100baseT_Half ; 
 int SUPPORTED_10baseT_Full ; 
 int SUPPORTED_10baseT_Half ; 
 int /*<<< orphan*/  ethtool_convert_link_mode_to_legacy_u32 (int*,int /*<<< orphan*/ ) ; 
 struct sky2_port* netdev_priv (struct net_device*) ; 
 scalar_t__ netif_running (struct net_device*) ; 
 scalar_t__ sky2_is_copper (struct sky2_hw const*) ; 
 int /*<<< orphan*/  sky2_phy_reinit (struct sky2_port*) ; 
 int /*<<< orphan*/  sky2_set_multicast (struct net_device*) ; 
 int sky2_supported_modes (struct sky2_hw const*) ; 

__attribute__((used)) static int sky2_set_link_ksettings(struct net_device *dev,
				   const struct ethtool_link_ksettings *cmd)
{
	struct sky2_port *sky2 = netdev_priv(dev);
	const struct sky2_hw *hw = sky2->hw;
	u32 supported = sky2_supported_modes(hw);
	u32 new_advertising;

	ethtool_convert_link_mode_to_legacy_u32(&new_advertising,
						cmd->link_modes.advertising);

	if (cmd->base.autoneg == AUTONEG_ENABLE) {
		if (new_advertising & ~supported)
			return -EINVAL;

		if (sky2_is_copper(hw))
			sky2->advertising = new_advertising |
					    ADVERTISED_TP |
					    ADVERTISED_Autoneg;
		else
			sky2->advertising = new_advertising |
					    ADVERTISED_FIBRE |
					    ADVERTISED_Autoneg;

		sky2->flags |= SKY2_FLAG_AUTO_SPEED;
		sky2->duplex = -1;
		sky2->speed = -1;
	} else {
		u32 setting;
		u32 speed = cmd->base.speed;

		switch (speed) {
		case SPEED_1000:
			if (cmd->base.duplex == DUPLEX_FULL)
				setting = SUPPORTED_1000baseT_Full;
			else if (cmd->base.duplex == DUPLEX_HALF)
				setting = SUPPORTED_1000baseT_Half;
			else
				return -EINVAL;
			break;
		case SPEED_100:
			if (cmd->base.duplex == DUPLEX_FULL)
				setting = SUPPORTED_100baseT_Full;
			else if (cmd->base.duplex == DUPLEX_HALF)
				setting = SUPPORTED_100baseT_Half;
			else
				return -EINVAL;
			break;

		case SPEED_10:
			if (cmd->base.duplex == DUPLEX_FULL)
				setting = SUPPORTED_10baseT_Full;
			else if (cmd->base.duplex == DUPLEX_HALF)
				setting = SUPPORTED_10baseT_Half;
			else
				return -EINVAL;
			break;
		default:
			return -EINVAL;
		}

		if ((setting & supported) == 0)
			return -EINVAL;

		sky2->speed = speed;
		sky2->duplex = cmd->base.duplex;
		sky2->flags &= ~SKY2_FLAG_AUTO_SPEED;
	}

	if (netif_running(dev)) {
		sky2_phy_reinit(sky2);
		sky2_set_multicast(dev);
	}

	return 0;
}