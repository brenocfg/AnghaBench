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
typedef  int u32 ;
struct net_device {scalar_t__ mtu; } ;
struct TYPE_2__ {scalar_t__ type; } ;
struct e1000_hw {TYPE_1__ mac; } ;
struct e1000_adapter {int flags2; int /*<<< orphan*/  rx_ring; int /*<<< orphan*/  tx_ring; int /*<<< orphan*/  pdev; struct net_device* netdev; scalar_t__ link_duplex; scalar_t__ link_speed; int /*<<< orphan*/  stats64_lock; int /*<<< orphan*/  phy_info_timer; int /*<<< orphan*/  napi; int /*<<< orphan*/  state; struct e1000_hw hw; } ;

/* Variables and functions */
 int E1000_RCTL_EN ; 
 int E1000_TCTL_EN ; 
 scalar_t__ ETH_DATA_LEN ; 
 int FLAG2_NO_DISABLE_RX ; 
 int /*<<< orphan*/  RCTL ; 
 int /*<<< orphan*/  TCTL ; 
 int /*<<< orphan*/  __E1000_DOWN ; 
 int /*<<< orphan*/  del_timer_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  e1000_clean_rx_ring (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  e1000_clean_tx_ring (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  e1000_flush_desc_rings (struct e1000_adapter*) ; 
 int /*<<< orphan*/  e1000_irq_disable (struct e1000_adapter*) ; 
 scalar_t__ e1000_lv_jumbo_workaround_ich8lan (struct e1000_hw*,int) ; 
 scalar_t__ e1000_pch2lan ; 
 scalar_t__ e1000_pch_spt ; 
 int /*<<< orphan*/  e1000e_flush_descriptors (struct e1000_adapter*) ; 
 int /*<<< orphan*/  e1000e_reset (struct e1000_adapter*) ; 
 int /*<<< orphan*/  e1000e_update_stats (struct e1000_adapter*) ; 
 int /*<<< orphan*/  e1e_flush () ; 
 int /*<<< orphan*/  e_dbg (char*) ; 
 int er32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ew32 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  napi_synchronize (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  netif_carrier_off (struct net_device*) ; 
 int /*<<< orphan*/  netif_stop_queue (struct net_device*) ; 
 int /*<<< orphan*/  pci_channel_offline (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

void e1000e_down(struct e1000_adapter *adapter, bool reset)
{
	struct net_device *netdev = adapter->netdev;
	struct e1000_hw *hw = &adapter->hw;
	u32 tctl, rctl;

	/* signal that we're down so the interrupt handler does not
	 * reschedule our watchdog timer
	 */
	set_bit(__E1000_DOWN, &adapter->state);

	netif_carrier_off(netdev);

	/* disable receives in the hardware */
	rctl = er32(RCTL);
	if (!(adapter->flags2 & FLAG2_NO_DISABLE_RX))
		ew32(RCTL, rctl & ~E1000_RCTL_EN);
	/* flush and sleep below */

	netif_stop_queue(netdev);

	/* disable transmits in the hardware */
	tctl = er32(TCTL);
	tctl &= ~E1000_TCTL_EN;
	ew32(TCTL, tctl);

	/* flush both disables and wait for them to finish */
	e1e_flush();
	usleep_range(10000, 11000);

	e1000_irq_disable(adapter);

	napi_synchronize(&adapter->napi);

	del_timer_sync(&adapter->phy_info_timer);

	spin_lock(&adapter->stats64_lock);
	e1000e_update_stats(adapter);
	spin_unlock(&adapter->stats64_lock);

	e1000e_flush_descriptors(adapter);

	adapter->link_speed = 0;
	adapter->link_duplex = 0;

	/* Disable Si errata workaround on PCHx for jumbo frame flow */
	if ((hw->mac.type >= e1000_pch2lan) &&
	    (adapter->netdev->mtu > ETH_DATA_LEN) &&
	    e1000_lv_jumbo_workaround_ich8lan(hw, false))
		e_dbg("failed to disable jumbo frame workaround mode\n");

	if (!pci_channel_offline(adapter->pdev)) {
		if (reset)
			e1000e_reset(adapter);
		else if (hw->mac.type >= e1000_pch_spt)
			e1000_flush_desc_rings(adapter);
	}
	e1000_clean_tx_ring(adapter->tx_ring);
	e1000_clean_rx_ring(adapter->rx_ring);
}