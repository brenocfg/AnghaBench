#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct timer_list {int dummy; } ;
struct net_device {int dummy; } ;
struct ixgb_desc_ring {scalar_t__ count; } ;
struct TYPE_5__ {scalar_t__ type; } ;
struct TYPE_6__ {TYPE_1__ fc; scalar_t__ link_up; } ;
struct ixgb_adapter {int link_speed; int detect_tx_hung; int /*<<< orphan*/  watchdog_timer; TYPE_2__ hw; int /*<<< orphan*/  tx_timeout_task; scalar_t__ link_duplex; struct ixgb_desc_ring tx_ring; struct net_device* netdev; } ;

/* Variables and functions */
 scalar_t__ FULL_DUPLEX ; 
 int HZ ; 
 int /*<<< orphan*/  ICS ; 
 scalar_t__ IXGB_DESC_UNUSED (struct ixgb_desc_ring*) ; 
 int /*<<< orphan*/  IXGB_INT_TXDW ; 
 int /*<<< orphan*/  IXGB_WRITE_REG (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct ixgb_adapter* adapter ; 
 struct ixgb_adapter* from_timer (int /*<<< orphan*/ ,struct timer_list*,int /*<<< orphan*/ ) ; 
 scalar_t__ ixgb_check_for_bad_link (TYPE_2__*) ; 
 int /*<<< orphan*/  ixgb_check_for_link (TYPE_2__*) ; 
 scalar_t__ ixgb_fc_full ; 
 scalar_t__ ixgb_fc_rx_pause ; 
 scalar_t__ ixgb_fc_tx_pause ; 
 int /*<<< orphan*/  ixgb_update_stats (struct ixgb_adapter*) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  netdev_info (struct net_device*,char*,...) ; 
 int /*<<< orphan*/  netif_carrier_off (struct net_device*) ; 
 scalar_t__ netif_carrier_ok (struct net_device*) ; 
 int /*<<< orphan*/  netif_carrier_on (struct net_device*) ; 
 int /*<<< orphan*/  netif_stop_queue (struct net_device*) ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  watchdog_timer ; 

__attribute__((used)) static void
ixgb_watchdog(struct timer_list *t)
{
	struct ixgb_adapter *adapter = from_timer(adapter, t, watchdog_timer);
	struct net_device *netdev = adapter->netdev;
	struct ixgb_desc_ring *txdr = &adapter->tx_ring;

	ixgb_check_for_link(&adapter->hw);

	if (ixgb_check_for_bad_link(&adapter->hw)) {
		/* force the reset path */
		netif_stop_queue(netdev);
	}

	if (adapter->hw.link_up) {
		if (!netif_carrier_ok(netdev)) {
			netdev_info(netdev,
				    "NIC Link is Up 10 Gbps Full Duplex, Flow Control: %s\n",
				    (adapter->hw.fc.type == ixgb_fc_full) ?
				    "RX/TX" :
				    (adapter->hw.fc.type == ixgb_fc_rx_pause) ?
				     "RX" :
				    (adapter->hw.fc.type == ixgb_fc_tx_pause) ?
				    "TX" : "None");
			adapter->link_speed = 10000;
			adapter->link_duplex = FULL_DUPLEX;
			netif_carrier_on(netdev);
		}
	} else {
		if (netif_carrier_ok(netdev)) {
			adapter->link_speed = 0;
			adapter->link_duplex = 0;
			netdev_info(netdev, "NIC Link is Down\n");
			netif_carrier_off(netdev);
		}
	}

	ixgb_update_stats(adapter);

	if (!netif_carrier_ok(netdev)) {
		if (IXGB_DESC_UNUSED(txdr) + 1 < txdr->count) {
			/* We've lost link, so the controller stops DMA,
			 * but we've got queued Tx work that's never going
			 * to get done, so reset controller to flush Tx.
			 * (Do the reset outside of interrupt context). */
			schedule_work(&adapter->tx_timeout_task);
			/* return immediately since reset is imminent */
			return;
		}
	}

	/* Force detection of hung controller every watchdog period */
	adapter->detect_tx_hung = true;

	/* generate an interrupt to force clean up of any stragglers */
	IXGB_WRITE_REG(&adapter->hw, ICS, IXGB_INT_TXDW);

	/* Reset the timer */
	mod_timer(&adapter->watchdog_timer, jiffies + 2 * HZ);
}