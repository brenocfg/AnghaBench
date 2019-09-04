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
typedef  int /*<<< orphan*/  u32 ;
struct net_device {int dummy; } ;
struct nes_vnic {struct nes_device* nesdev; } ;
struct nes_device {int disable_tx_flow_control; int mac_index; int disable_rx_flow_control; } ;
struct ethtool_pauseparam {int tx_pause; int rx_pause; scalar_t__ autoneg; } ;

/* Variables and functions */
 scalar_t__ NES_IDX_MAC_TX_CONFIG ; 
 int /*<<< orphan*/  NES_IDX_MAC_TX_CONFIG_ENABLE_PAUSE ; 
 scalar_t__ NES_IDX_MPP_DEBUG ; 
 int /*<<< orphan*/  NES_IDX_MPP_DEBUG_PORT_DISABLE_PAUSE ; 
 int /*<<< orphan*/  nes_read_indexed (struct nes_device*,scalar_t__) ; 
 int /*<<< orphan*/  nes_write_indexed (struct nes_device*,scalar_t__,int /*<<< orphan*/ ) ; 
 struct nes_vnic* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int nes_netdev_set_pauseparam(struct net_device *netdev,
		struct ethtool_pauseparam *et_pauseparam)
{
	struct nes_vnic *nesvnic = netdev_priv(netdev);
	struct nes_device *nesdev = nesvnic->nesdev;
	u32 u32temp;

	if (et_pauseparam->autoneg) {
		/* TODO: should return unsupported */
		return 0;
	}
	if ((et_pauseparam->tx_pause == 1) && (nesdev->disable_tx_flow_control == 1)) {
		u32temp = nes_read_indexed(nesdev,
				NES_IDX_MAC_TX_CONFIG + (nesdev->mac_index*0x200));
		u32temp |= NES_IDX_MAC_TX_CONFIG_ENABLE_PAUSE;
		nes_write_indexed(nesdev,
				NES_IDX_MAC_TX_CONFIG + (nesdev->mac_index*0x200), u32temp);
		nesdev->disable_tx_flow_control = 0;
	} else if ((et_pauseparam->tx_pause == 0) && (nesdev->disable_tx_flow_control == 0)) {
		u32temp = nes_read_indexed(nesdev,
				NES_IDX_MAC_TX_CONFIG + (nesdev->mac_index*0x200));
		u32temp &= ~NES_IDX_MAC_TX_CONFIG_ENABLE_PAUSE;
		nes_write_indexed(nesdev,
				NES_IDX_MAC_TX_CONFIG + (nesdev->mac_index*0x200), u32temp);
		nesdev->disable_tx_flow_control = 1;
	}
	if ((et_pauseparam->rx_pause == 1) && (nesdev->disable_rx_flow_control == 1)) {
		u32temp = nes_read_indexed(nesdev,
				NES_IDX_MPP_DEBUG + (nesdev->mac_index*0x40));
		u32temp &= ~NES_IDX_MPP_DEBUG_PORT_DISABLE_PAUSE;
		nes_write_indexed(nesdev,
				NES_IDX_MPP_DEBUG + (nesdev->mac_index*0x40), u32temp);
		nesdev->disable_rx_flow_control = 0;
	} else if ((et_pauseparam->rx_pause == 0) && (nesdev->disable_rx_flow_control == 0)) {
		u32temp = nes_read_indexed(nesdev,
				NES_IDX_MPP_DEBUG + (nesdev->mac_index*0x40));
		u32temp |= NES_IDX_MPP_DEBUG_PORT_DISABLE_PAUSE;
		nes_write_indexed(nesdev,
				NES_IDX_MPP_DEBUG + (nesdev->mac_index*0x40), u32temp);
		nesdev->disable_rx_flow_control = 1;
	}

	return 0;
}