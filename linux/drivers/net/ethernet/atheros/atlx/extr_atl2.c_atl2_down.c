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
struct atl2_adapter {int link_duplex; int /*<<< orphan*/  link_speed; int /*<<< orphan*/  cfg_phy; int /*<<< orphan*/  phy_config_timer; int /*<<< orphan*/  watchdog_timer; int /*<<< orphan*/  hw; int /*<<< orphan*/  flags; struct net_device* netdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  SPEED_0 ; 
 int /*<<< orphan*/  __ATL2_DOWN ; 
 int /*<<< orphan*/  atl2_irq_disable (struct atl2_adapter*) ; 
 int /*<<< orphan*/  atl2_reset_hw (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  del_timer_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  netif_carrier_off (struct net_device*) ; 
 int /*<<< orphan*/  netif_tx_disable (struct net_device*) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void atl2_down(struct atl2_adapter *adapter)
{
	struct net_device *netdev = adapter->netdev;

	/* signal that we're down so the interrupt handler does not
	 * reschedule our watchdog timer */
	set_bit(__ATL2_DOWN, &adapter->flags);

	netif_tx_disable(netdev);

	/* reset MAC to disable all RX/TX */
	atl2_reset_hw(&adapter->hw);
	msleep(1);

	atl2_irq_disable(adapter);

	del_timer_sync(&adapter->watchdog_timer);
	del_timer_sync(&adapter->phy_config_timer);
	clear_bit(0, &adapter->cfg_phy);

	netif_carrier_off(netdev);
	adapter->link_speed = SPEED_0;
	adapter->link_duplex = -1;
}