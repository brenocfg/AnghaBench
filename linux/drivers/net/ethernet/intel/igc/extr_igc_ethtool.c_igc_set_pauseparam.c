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
struct net_device {int dummy; } ;
struct TYPE_4__ {scalar_t__ media_type; } ;
struct TYPE_3__ {int /*<<< orphan*/  requested_mode; int /*<<< orphan*/  current_mode; } ;
struct igc_hw {TYPE_2__ phy; TYPE_1__ fc; } ;
struct igc_adapter {scalar_t__ fc_autoneg; int /*<<< orphan*/  state; int /*<<< orphan*/  netdev; struct igc_hw hw; } ;
struct ethtool_pauseparam {scalar_t__ autoneg; scalar_t__ tx_pause; scalar_t__ rx_pause; } ;

/* Variables and functions */
 scalar_t__ AUTONEG_ENABLE ; 
 int /*<<< orphan*/  __IGC_RESETTING ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  igc_down (struct igc_adapter*) ; 
 int /*<<< orphan*/  igc_fc_default ; 
 int /*<<< orphan*/  igc_fc_full ; 
 int /*<<< orphan*/  igc_fc_none ; 
 int /*<<< orphan*/  igc_fc_rx_pause ; 
 int /*<<< orphan*/  igc_fc_tx_pause ; 
 int igc_force_mac_fc (struct igc_hw*) ; 
 scalar_t__ igc_media_type_copper ; 
 int /*<<< orphan*/  igc_reset (struct igc_adapter*) ; 
 int igc_setup_link (struct igc_hw*) ; 
 int /*<<< orphan*/  igc_up (struct igc_adapter*) ; 
 struct igc_adapter* netdev_priv (struct net_device*) ; 
 scalar_t__ netif_running (int /*<<< orphan*/ ) ; 
 scalar_t__ test_and_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static int igc_set_pauseparam(struct net_device *netdev,
			      struct ethtool_pauseparam *pause)
{
	struct igc_adapter *adapter = netdev_priv(netdev);
	struct igc_hw *hw = &adapter->hw;
	int retval = 0;

	adapter->fc_autoneg = pause->autoneg;

	while (test_and_set_bit(__IGC_RESETTING, &adapter->state))
		usleep_range(1000, 2000);

	if (adapter->fc_autoneg == AUTONEG_ENABLE) {
		hw->fc.requested_mode = igc_fc_default;
		if (netif_running(adapter->netdev)) {
			igc_down(adapter);
			igc_up(adapter);
		} else {
			igc_reset(adapter);
		}
	} else {
		if (pause->rx_pause && pause->tx_pause)
			hw->fc.requested_mode = igc_fc_full;
		else if (pause->rx_pause && !pause->tx_pause)
			hw->fc.requested_mode = igc_fc_rx_pause;
		else if (!pause->rx_pause && pause->tx_pause)
			hw->fc.requested_mode = igc_fc_tx_pause;
		else if (!pause->rx_pause && !pause->tx_pause)
			hw->fc.requested_mode = igc_fc_none;

		hw->fc.current_mode = hw->fc.requested_mode;

		retval = ((hw->phy.media_type == igc_media_type_copper) ?
			  igc_force_mac_fc(hw) : igc_setup_link(hw));
	}

	clear_bit(__IGC_RESETTING, &adapter->state);
	return retval;
}