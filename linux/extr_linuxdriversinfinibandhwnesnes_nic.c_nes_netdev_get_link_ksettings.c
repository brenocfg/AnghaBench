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
typedef  scalar_t__ u8 ;
typedef  size_t u32 ;
typedef  int u16 ;
struct net_device {int dummy; } ;
struct nes_vnic {struct nes_device* nesdev; } ;
struct nes_device {size_t mac_index; struct nes_adapter* nesadapter; } ;
struct nes_adapter {scalar_t__* phy_type; scalar_t__* phy_index; int /*<<< orphan*/  phy_lock; scalar_t__ OneG_Mode; } ;
struct TYPE_4__ {int /*<<< orphan*/  advertising; int /*<<< orphan*/  supported; } ;
struct TYPE_3__ {size_t phy_address; void* autoneg; int /*<<< orphan*/  speed; int /*<<< orphan*/  port; int /*<<< orphan*/  duplex; } ;
struct ethtool_link_ksettings {TYPE_2__ link_modes; TYPE_1__ base; } ;

/* Variables and functions */
 size_t ADVERTISED_10000baseT_Full ; 
 size_t ADVERTISED_1000baseT_Full ; 
 size_t ADVERTISED_Autoneg ; 
 size_t ADVERTISED_FIBRE ; 
 void* AUTONEG_DISABLE ; 
 void* AUTONEG_ENABLE ; 
 int /*<<< orphan*/  DUPLEX_FULL ; 
 scalar_t__ NES_PHY_TYPE_ARGUS ; 
 scalar_t__ NES_PHY_TYPE_KR ; 
 scalar_t__ NES_PHY_TYPE_PUMA_1G ; 
 scalar_t__ NES_PHY_TYPE_SFP_D ; 
 int /*<<< orphan*/  PORT_FIBRE ; 
 int /*<<< orphan*/  PORT_MII ; 
 int /*<<< orphan*/  SPEED_1000 ; 
 int /*<<< orphan*/  SPEED_10000 ; 
 size_t SUPPORTED_10000baseT_Full ; 
 size_t SUPPORTED_1000baseT_Full ; 
 size_t SUPPORTED_Autoneg ; 
 size_t SUPPORTED_FIBRE ; 
 int /*<<< orphan*/  ethtool_convert_legacy_u32_to_link_mode (int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  nes_read_1G_phy_reg (struct nes_device*,int /*<<< orphan*/ ,scalar_t__,int*) ; 
 struct nes_vnic* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int nes_netdev_get_link_ksettings(struct net_device *netdev,
					 struct ethtool_link_ksettings *cmd)
{
	struct nes_vnic *nesvnic = netdev_priv(netdev);
	struct nes_device *nesdev = nesvnic->nesdev;
	struct nes_adapter *nesadapter = nesdev->nesadapter;
	u32 mac_index = nesdev->mac_index;
	u8 phy_type = nesadapter->phy_type[mac_index];
	u8 phy_index = nesadapter->phy_index[mac_index];
	u16 phy_data;
	u32 supported, advertising;

	cmd->base.duplex = DUPLEX_FULL;
	cmd->base.port   = PORT_MII;

	if (nesadapter->OneG_Mode) {
		cmd->base.speed = SPEED_1000;
		if (phy_type == NES_PHY_TYPE_PUMA_1G) {
			supported   = SUPPORTED_1000baseT_Full;
			advertising = ADVERTISED_1000baseT_Full;
			cmd->base.autoneg     = AUTONEG_DISABLE;
			cmd->base.phy_address = mac_index;
		} else {
			unsigned long flags;

			supported = SUPPORTED_1000baseT_Full
				| SUPPORTED_Autoneg;
			advertising = ADVERTISED_1000baseT_Full
				| ADVERTISED_Autoneg;
			spin_lock_irqsave(&nesadapter->phy_lock, flags);
			nes_read_1G_phy_reg(nesdev, 0, phy_index, &phy_data);
			spin_unlock_irqrestore(&nesadapter->phy_lock, flags);
			if (phy_data & 0x1000)
				cmd->base.autoneg = AUTONEG_ENABLE;
			else
				cmd->base.autoneg = AUTONEG_DISABLE;
			cmd->base.phy_address = phy_index;
		}
		ethtool_convert_legacy_u32_to_link_mode(
			cmd->link_modes.supported, supported);
		ethtool_convert_legacy_u32_to_link_mode(
			cmd->link_modes.advertising, advertising);
		return 0;
	}
	if ((phy_type == NES_PHY_TYPE_ARGUS) ||
	    (phy_type == NES_PHY_TYPE_SFP_D) ||
	    (phy_type == NES_PHY_TYPE_KR)) {
		cmd->base.port        = PORT_FIBRE;
		supported   = SUPPORTED_FIBRE;
		advertising = ADVERTISED_FIBRE;
		cmd->base.phy_address = phy_index;
	} else {
		supported   = SUPPORTED_10000baseT_Full;
		advertising = ADVERTISED_10000baseT_Full;
		cmd->base.phy_address = mac_index;
	}
	cmd->base.speed = SPEED_10000;
	cmd->base.autoneg = AUTONEG_DISABLE;
	ethtool_convert_legacy_u32_to_link_mode(cmd->link_modes.supported,
						supported);
	ethtool_convert_legacy_u32_to_link_mode(cmd->link_modes.advertising,
						advertising);

	return 0;
}