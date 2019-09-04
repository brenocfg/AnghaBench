#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_6__ {int /*<<< orphan*/  parent; } ;
struct net_device {TYPE_1__ dev; } ;
struct TYPE_10__ {int /*<<< orphan*/  advertising; int /*<<< orphan*/  supported; } ;
struct TYPE_9__ {int speed; scalar_t__ eth_tp_mdix_ctrl; void* eth_tp_mdix; int /*<<< orphan*/  autoneg; scalar_t__ duplex; int /*<<< orphan*/  port; int /*<<< orphan*/  phy_address; } ;
struct ethtool_link_ksettings {TYPE_5__ link_modes; TYPE_4__ base; } ;
struct TYPE_8__ {scalar_t__ media_type; scalar_t__ type; int autoneg_advertised; scalar_t__ mdix; scalar_t__ is_mdix; int /*<<< orphan*/  addr; } ;
struct TYPE_7__ {int autoneg; } ;
struct e1000_hw {TYPE_3__ phy; TYPE_2__ mac; } ;
struct e1000_adapter {int link_speed; scalar_t__ link_duplex; struct e1000_hw hw; } ;

/* Variables and functions */
 int ADVERTISED_1000baseT_Full ; 
 int ADVERTISED_Autoneg ; 
 int ADVERTISED_FIBRE ; 
 int ADVERTISED_TP ; 
 int /*<<< orphan*/  AUTONEG_DISABLE ; 
 int /*<<< orphan*/  AUTONEG_ENABLE ; 
 scalar_t__ AUTO_ALL_MODES ; 
 scalar_t__ DUPLEX_FULL ; 
 scalar_t__ DUPLEX_HALF ; 
 scalar_t__ DUPLEX_UNKNOWN ; 
 int E1000_STATUS_FD ; 
 int E1000_STATUS_LU ; 
 int E1000_STATUS_SPEED_100 ; 
 int E1000_STATUS_SPEED_1000 ; 
 void* ETH_TP_MDI ; 
 scalar_t__ ETH_TP_MDI_AUTO ; 
 void* ETH_TP_MDI_INVALID ; 
 void* ETH_TP_MDI_X ; 
 int /*<<< orphan*/  PORT_FIBRE ; 
 int /*<<< orphan*/  PORT_TP ; 
 int SPEED_10 ; 
 int SPEED_100 ; 
 int SPEED_1000 ; 
 int SPEED_UNKNOWN ; 
 int /*<<< orphan*/  STATUS ; 
 int SUPPORTED_1000baseT_Full ; 
 int SUPPORTED_100baseT_Full ; 
 int SUPPORTED_100baseT_Half ; 
 int SUPPORTED_10baseT_Full ; 
 int SUPPORTED_10baseT_Half ; 
 int SUPPORTED_Autoneg ; 
 int SUPPORTED_FIBRE ; 
 int SUPPORTED_TP ; 
 scalar_t__ e1000_media_type_copper ; 
 scalar_t__ e1000_media_type_fiber ; 
 scalar_t__ e1000_phy_ife ; 
 int er32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ethtool_convert_legacy_u32_to_link_mode (int /*<<< orphan*/ ,int) ; 
 struct e1000_adapter* netdev_priv (struct net_device*) ; 
 scalar_t__ netif_carrier_ok (struct net_device*) ; 
 scalar_t__ netif_running (struct net_device*) ; 
 int /*<<< orphan*/  pm_runtime_suspended (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int e1000_get_link_ksettings(struct net_device *netdev,
				    struct ethtool_link_ksettings *cmd)
{
	struct e1000_adapter *adapter = netdev_priv(netdev);
	struct e1000_hw *hw = &adapter->hw;
	u32 speed, supported, advertising;

	if (hw->phy.media_type == e1000_media_type_copper) {
		supported = (SUPPORTED_10baseT_Half |
			     SUPPORTED_10baseT_Full |
			     SUPPORTED_100baseT_Half |
			     SUPPORTED_100baseT_Full |
			     SUPPORTED_1000baseT_Full |
			     SUPPORTED_Autoneg |
			     SUPPORTED_TP);
		if (hw->phy.type == e1000_phy_ife)
			supported &= ~SUPPORTED_1000baseT_Full;
		advertising = ADVERTISED_TP;

		if (hw->mac.autoneg == 1) {
			advertising |= ADVERTISED_Autoneg;
			/* the e1000 autoneg seems to match ethtool nicely */
			advertising |= hw->phy.autoneg_advertised;
		}

		cmd->base.port = PORT_TP;
		cmd->base.phy_address = hw->phy.addr;
	} else {
		supported   = (SUPPORTED_1000baseT_Full |
			       SUPPORTED_FIBRE |
			       SUPPORTED_Autoneg);

		advertising = (ADVERTISED_1000baseT_Full |
			       ADVERTISED_FIBRE |
			       ADVERTISED_Autoneg);

		cmd->base.port = PORT_FIBRE;
	}

	speed = SPEED_UNKNOWN;
	cmd->base.duplex = DUPLEX_UNKNOWN;

	if (netif_running(netdev)) {
		if (netif_carrier_ok(netdev)) {
			speed = adapter->link_speed;
			cmd->base.duplex = adapter->link_duplex - 1;
		}
	} else if (!pm_runtime_suspended(netdev->dev.parent)) {
		u32 status = er32(STATUS);

		if (status & E1000_STATUS_LU) {
			if (status & E1000_STATUS_SPEED_1000)
				speed = SPEED_1000;
			else if (status & E1000_STATUS_SPEED_100)
				speed = SPEED_100;
			else
				speed = SPEED_10;

			if (status & E1000_STATUS_FD)
				cmd->base.duplex = DUPLEX_FULL;
			else
				cmd->base.duplex = DUPLEX_HALF;
		}
	}

	cmd->base.speed = speed;
	cmd->base.autoneg = ((hw->phy.media_type == e1000_media_type_fiber) ||
			 hw->mac.autoneg) ? AUTONEG_ENABLE : AUTONEG_DISABLE;

	/* MDI-X => 2; MDI =>1; Invalid =>0 */
	if ((hw->phy.media_type == e1000_media_type_copper) &&
	    netif_carrier_ok(netdev))
		cmd->base.eth_tp_mdix = hw->phy.is_mdix ?
			ETH_TP_MDI_X : ETH_TP_MDI;
	else
		cmd->base.eth_tp_mdix = ETH_TP_MDI_INVALID;

	if (hw->phy.mdix == AUTO_ALL_MODES)
		cmd->base.eth_tp_mdix_ctrl = ETH_TP_MDI_AUTO;
	else
		cmd->base.eth_tp_mdix_ctrl = hw->phy.mdix;

	if (hw->phy.media_type != e1000_media_type_copper)
		cmd->base.eth_tp_mdix_ctrl = ETH_TP_MDI_INVALID;

	ethtool_convert_legacy_u32_to_link_mode(cmd->link_modes.supported,
						supported);
	ethtool_convert_legacy_u32_to_link_mode(cmd->link_modes.advertising,
						advertising);

	return 0;
}