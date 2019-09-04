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
typedef  scalar_t__ u16 ;
struct net_device {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  advertising; int /*<<< orphan*/  supported; } ;
struct TYPE_3__ {int /*<<< orphan*/  autoneg; int /*<<< orphan*/  duplex; scalar_t__ speed; scalar_t__ phy_address; int /*<<< orphan*/  port; } ;
struct ethtool_link_ksettings {TYPE_2__ link_modes; TYPE_1__ base; } ;
struct atl1_hw {scalar_t__ media_type; } ;
struct atl1_adapter {int /*<<< orphan*/  netdev; struct atl1_hw hw; } ;

/* Variables and functions */
 int ADVERTISED_1000baseT_Full ; 
 int ADVERTISED_100baseT_Full ; 
 int ADVERTISED_100baseT_Half ; 
 int ADVERTISED_10baseT_Full ; 
 int ADVERTISED_10baseT_Half ; 
 int ADVERTISED_Autoneg ; 
 int ADVERTISED_TP ; 
 int /*<<< orphan*/  AUTONEG_DISABLE ; 
 int /*<<< orphan*/  AUTONEG_ENABLE ; 
 int /*<<< orphan*/  DUPLEX_FULL ; 
 int /*<<< orphan*/  DUPLEX_HALF ; 
 int /*<<< orphan*/  DUPLEX_UNKNOWN ; 
 scalar_t__ FULL_DUPLEX ; 
 scalar_t__ MEDIA_TYPE_1000M_FULL ; 
 scalar_t__ MEDIA_TYPE_AUTO_SENSOR ; 
 int /*<<< orphan*/  PORT_TP ; 
 scalar_t__ SPEED_UNKNOWN ; 
 int SUPPORTED_1000baseT_Full ; 
 int SUPPORTED_100baseT_Full ; 
 int SUPPORTED_100baseT_Half ; 
 int SUPPORTED_10baseT_Full ; 
 int SUPPORTED_10baseT_Half ; 
 int SUPPORTED_Autoneg ; 
 int SUPPORTED_TP ; 
 int /*<<< orphan*/  atl1_get_speed_and_duplex (struct atl1_hw*,scalar_t__*,scalar_t__*) ; 
 int /*<<< orphan*/  ethtool_convert_legacy_u32_to_link_mode (int /*<<< orphan*/ ,int) ; 
 struct atl1_adapter* netdev_priv (struct net_device*) ; 
 scalar_t__ netif_carrier_ok (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int atl1_get_link_ksettings(struct net_device *netdev,
				   struct ethtool_link_ksettings *cmd)
{
	struct atl1_adapter *adapter = netdev_priv(netdev);
	struct atl1_hw *hw = &adapter->hw;
	u32 supported, advertising;

	supported = (SUPPORTED_10baseT_Half |
			   SUPPORTED_10baseT_Full |
			   SUPPORTED_100baseT_Half |
			   SUPPORTED_100baseT_Full |
			   SUPPORTED_1000baseT_Full |
			   SUPPORTED_Autoneg | SUPPORTED_TP);
	advertising = ADVERTISED_TP;
	if (hw->media_type == MEDIA_TYPE_AUTO_SENSOR ||
	    hw->media_type == MEDIA_TYPE_1000M_FULL) {
		advertising |= ADVERTISED_Autoneg;
		if (hw->media_type == MEDIA_TYPE_AUTO_SENSOR) {
			advertising |= ADVERTISED_Autoneg;
			advertising |=
			    (ADVERTISED_10baseT_Half |
			     ADVERTISED_10baseT_Full |
			     ADVERTISED_100baseT_Half |
			     ADVERTISED_100baseT_Full |
			     ADVERTISED_1000baseT_Full);
		} else
			advertising |= (ADVERTISED_1000baseT_Full);
	}
	cmd->base.port = PORT_TP;
	cmd->base.phy_address = 0;

	if (netif_carrier_ok(adapter->netdev)) {
		u16 link_speed, link_duplex;
		atl1_get_speed_and_duplex(hw, &link_speed, &link_duplex);
		cmd->base.speed = link_speed;
		if (link_duplex == FULL_DUPLEX)
			cmd->base.duplex = DUPLEX_FULL;
		else
			cmd->base.duplex = DUPLEX_HALF;
	} else {
		cmd->base.speed = SPEED_UNKNOWN;
		cmd->base.duplex = DUPLEX_UNKNOWN;
	}
	if (hw->media_type == MEDIA_TYPE_AUTO_SENSOR ||
	    hw->media_type == MEDIA_TYPE_1000M_FULL)
		cmd->base.autoneg = AUTONEG_ENABLE;
	else
		cmd->base.autoneg = AUTONEG_DISABLE;

	ethtool_convert_legacy_u32_to_link_mode(cmd->link_modes.supported,
						supported);
	ethtool_convert_legacy_u32_to_link_mode(cmd->link_modes.advertising,
						advertising);

	return 0;
}