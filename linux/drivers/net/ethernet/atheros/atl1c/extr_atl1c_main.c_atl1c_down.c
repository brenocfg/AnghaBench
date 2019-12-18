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
struct atl1c_adapter {int link_duplex; int /*<<< orphan*/  link_speed; int /*<<< orphan*/  hw; int /*<<< orphan*/  napi; int /*<<< orphan*/  flags; scalar_t__ work_event; struct net_device* netdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  SPEED_0 ; 
 int /*<<< orphan*/  __AT_DOWN ; 
 int /*<<< orphan*/  atl1c_del_timer (struct atl1c_adapter*) ; 
 int /*<<< orphan*/  atl1c_disable_l0s_l1 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atl1c_free_irq (struct atl1c_adapter*) ; 
 int /*<<< orphan*/  atl1c_irq_disable (struct atl1c_adapter*) ; 
 int /*<<< orphan*/  atl1c_reset_dma_ring (struct atl1c_adapter*) ; 
 int /*<<< orphan*/  atl1c_reset_mac (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  napi_disable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  netif_carrier_off (struct net_device*) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void atl1c_down(struct atl1c_adapter *adapter)
{
	struct net_device *netdev = adapter->netdev;

	atl1c_del_timer(adapter);
	adapter->work_event = 0; /* clear all event */
	/* signal that we're down so the interrupt handler does not
	 * reschedule our watchdog timer */
	set_bit(__AT_DOWN, &adapter->flags);
	netif_carrier_off(netdev);
	napi_disable(&adapter->napi);
	atl1c_irq_disable(adapter);
	atl1c_free_irq(adapter);
	/* disable ASPM if device inactive */
	atl1c_disable_l0s_l1(&adapter->hw);
	/* reset MAC to disable all RX/TX */
	atl1c_reset_mac(&adapter->hw);
	msleep(1);

	adapter->link_speed = SPEED_0;
	adapter->link_duplex = -1;
	atl1c_reset_dma_ring(adapter);
}