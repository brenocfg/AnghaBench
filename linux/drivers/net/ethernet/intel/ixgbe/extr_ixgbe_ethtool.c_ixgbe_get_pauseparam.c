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
struct net_device {int dummy; } ;
struct TYPE_2__ {scalar_t__ current_mode; int /*<<< orphan*/  disable_fc_autoneg; } ;
struct ixgbe_hw {TYPE_1__ fc; } ;
struct ixgbe_adapter {struct ixgbe_hw hw; } ;
struct ethtool_pauseparam {int autoneg; int rx_pause; int tx_pause; } ;

/* Variables and functions */
 scalar_t__ ixgbe_device_supports_autoneg_fc (struct ixgbe_hw*) ; 
 scalar_t__ ixgbe_fc_full ; 
 scalar_t__ ixgbe_fc_rx_pause ; 
 scalar_t__ ixgbe_fc_tx_pause ; 
 struct ixgbe_adapter* netdev_priv (struct net_device*) ; 

__attribute__((used)) static void ixgbe_get_pauseparam(struct net_device *netdev,
				 struct ethtool_pauseparam *pause)
{
	struct ixgbe_adapter *adapter = netdev_priv(netdev);
	struct ixgbe_hw *hw = &adapter->hw;

	if (ixgbe_device_supports_autoneg_fc(hw) &&
	    !hw->fc.disable_fc_autoneg)
		pause->autoneg = 1;
	else
		pause->autoneg = 0;

	if (hw->fc.current_mode == ixgbe_fc_rx_pause) {
		pause->rx_pause = 1;
	} else if (hw->fc.current_mode == ixgbe_fc_tx_pause) {
		pause->tx_pause = 1;
	} else if (hw->fc.current_mode == ixgbe_fc_full) {
		pause->rx_pause = 1;
		pause->tx_pause = 1;
	}
}