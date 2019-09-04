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
struct net_device {int dummy; } ;
struct atl1e_adapter {int link_duplex; int /*<<< orphan*/  link_speed; int /*<<< orphan*/  napi; int /*<<< orphan*/  hw; int /*<<< orphan*/  flags; struct net_device* netdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  SPEED_0 ; 
 int /*<<< orphan*/  __AT_DOWN ; 
 int /*<<< orphan*/  atl1e_clean_rx_ring (struct atl1e_adapter*) ; 
 int /*<<< orphan*/  atl1e_clean_tx_ring (struct atl1e_adapter*) ; 
 int /*<<< orphan*/  atl1e_del_timer (struct atl1e_adapter*) ; 
 int /*<<< orphan*/  atl1e_irq_disable (struct atl1e_adapter*) ; 
 int /*<<< orphan*/  atl1e_reset_hw (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  napi_disable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  netif_carrier_off (struct net_device*) ; 
 int /*<<< orphan*/  netif_stop_queue (struct net_device*) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void atl1e_down(struct atl1e_adapter *adapter)
{
	struct net_device *netdev = adapter->netdev;

	/* signal that we're down so the interrupt handler does not
	 * reschedule our watchdog timer */
	set_bit(__AT_DOWN, &adapter->flags);

	netif_stop_queue(netdev);

	/* reset MAC to disable all RX/TX */
	atl1e_reset_hw(&adapter->hw);
	msleep(1);

	napi_disable(&adapter->napi);
	atl1e_del_timer(adapter);
	atl1e_irq_disable(adapter);

	netif_carrier_off(netdev);
	adapter->link_speed = SPEED_0;
	adapter->link_duplex = -1;
	atl1e_clean_tx_ring(adapter);
	atl1e_clean_rx_ring(adapter);
}