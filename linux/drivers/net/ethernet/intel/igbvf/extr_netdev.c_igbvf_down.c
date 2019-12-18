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
struct net_device {int dummy; } ;
struct e1000_hw {int dummy; } ;
struct igbvf_adapter {TYPE_1__* rx_ring; int /*<<< orphan*/  tx_ring; scalar_t__ link_duplex; scalar_t__ link_speed; int /*<<< orphan*/  watchdog_timer; int /*<<< orphan*/  state; struct e1000_hw hw; struct net_device* netdev; } ;
struct TYPE_2__ {int /*<<< orphan*/  napi; } ;

/* Variables and functions */
 int E1000_RXDCTL_QUEUE_ENABLE ; 
 int E1000_TXDCTL_QUEUE_ENABLE ; 
 int /*<<< orphan*/  RXDCTL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TXDCTL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __IGBVF_DOWN ; 
 int /*<<< orphan*/  del_timer_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  e1e_flush () ; 
 int er32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ew32 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  igbvf_clean_rx_ring (TYPE_1__*) ; 
 int /*<<< orphan*/  igbvf_clean_tx_ring (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  igbvf_irq_disable (struct igbvf_adapter*) ; 
 int /*<<< orphan*/  igbvf_reset (struct igbvf_adapter*) ; 
 int /*<<< orphan*/  igbvf_update_stats (struct igbvf_adapter*) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  napi_disable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  netif_carrier_off (struct net_device*) ; 
 int /*<<< orphan*/  netif_stop_queue (struct net_device*) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void igbvf_down(struct igbvf_adapter *adapter)
{
	struct net_device *netdev = adapter->netdev;
	struct e1000_hw *hw = &adapter->hw;
	u32 rxdctl, txdctl;

	/* signal that we're down so the interrupt handler does not
	 * reschedule our watchdog timer
	 */
	set_bit(__IGBVF_DOWN, &adapter->state);

	/* disable receives in the hardware */
	rxdctl = er32(RXDCTL(0));
	ew32(RXDCTL(0), rxdctl & ~E1000_RXDCTL_QUEUE_ENABLE);

	netif_carrier_off(netdev);
	netif_stop_queue(netdev);

	/* disable transmits in the hardware */
	txdctl = er32(TXDCTL(0));
	ew32(TXDCTL(0), txdctl & ~E1000_TXDCTL_QUEUE_ENABLE);

	/* flush both disables and wait for them to finish */
	e1e_flush();
	msleep(10);

	napi_disable(&adapter->rx_ring->napi);

	igbvf_irq_disable(adapter);

	del_timer_sync(&adapter->watchdog_timer);

	/* record the stats before reset*/
	igbvf_update_stats(adapter);

	adapter->link_speed = 0;
	adapter->link_duplex = 0;

	igbvf_reset(adapter);
	igbvf_clean_tx_ring(adapter->tx_ring);
	igbvf_clean_rx_ring(adapter->rx_ring);
}