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
struct TYPE_2__ {scalar_t__ fc_autoneg; int /*<<< orphan*/  fc; } ;
struct pch_gbe_hw {TYPE_1__ mac; } ;
struct pch_gbe_adapter {int /*<<< orphan*/  netdev; struct pch_gbe_hw hw; } ;
struct net_device {int dummy; } ;
struct ethtool_pauseparam {scalar_t__ autoneg; scalar_t__ tx_pause; scalar_t__ rx_pause; } ;

/* Variables and functions */
 scalar_t__ AUTONEG_ENABLE ; 
 int /*<<< orphan*/  PCH_GBE_FC_FULL ; 
 int /*<<< orphan*/  PCH_GBE_FC_NONE ; 
 int /*<<< orphan*/  PCH_GBE_FC_RX_PAUSE ; 
 int /*<<< orphan*/  PCH_GBE_FC_TX_PAUSE ; 
 struct pch_gbe_adapter* netdev_priv (struct net_device*) ; 
 scalar_t__ netif_running (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pch_gbe_down (struct pch_gbe_adapter*) ; 
 int pch_gbe_mac_force_mac_fc (struct pch_gbe_hw*) ; 
 int /*<<< orphan*/  pch_gbe_reset (struct pch_gbe_adapter*) ; 
 int pch_gbe_up (struct pch_gbe_adapter*) ; 

__attribute__((used)) static int pch_gbe_set_pauseparam(struct net_device *netdev,
				       struct ethtool_pauseparam *pause)
{
	struct pch_gbe_adapter *adapter = netdev_priv(netdev);
	struct pch_gbe_hw *hw = &adapter->hw;
	int ret = 0;

	hw->mac.fc_autoneg = pause->autoneg;
	if ((pause->rx_pause) && (pause->tx_pause))
		hw->mac.fc = PCH_GBE_FC_FULL;
	else if ((pause->rx_pause) && (!pause->tx_pause))
		hw->mac.fc = PCH_GBE_FC_RX_PAUSE;
	else if ((!pause->rx_pause) && (pause->tx_pause))
		hw->mac.fc = PCH_GBE_FC_TX_PAUSE;
	else if ((!pause->rx_pause) && (!pause->tx_pause))
		hw->mac.fc = PCH_GBE_FC_NONE;

	if (hw->mac.fc_autoneg == AUTONEG_ENABLE) {
		if ((netif_running(adapter->netdev))) {
			pch_gbe_down(adapter);
			ret = pch_gbe_up(adapter);
		} else {
			pch_gbe_reset(adapter);
		}
	} else {
		ret = pch_gbe_mac_force_mac_fc(hw);
	}
	return ret;
}