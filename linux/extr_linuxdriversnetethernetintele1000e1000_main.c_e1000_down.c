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
typedef  int u32 ;
struct net_device {int dummy; } ;
struct e1000_hw {int dummy; } ;
struct e1000_adapter {scalar_t__ link_duplex; scalar_t__ link_speed; int /*<<< orphan*/  napi; struct net_device* netdev; struct e1000_hw hw; } ;

/* Variables and functions */
 int E1000_RCTL_EN ; 
 int E1000_TCTL_EN ; 
 int /*<<< orphan*/  E1000_WRITE_FLUSH () ; 
 int /*<<< orphan*/  RCTL ; 
 int /*<<< orphan*/  TCTL ; 
 int /*<<< orphan*/  e1000_clean_all_rx_rings (struct e1000_adapter*) ; 
 int /*<<< orphan*/  e1000_clean_all_tx_rings (struct e1000_adapter*) ; 
 int /*<<< orphan*/  e1000_down_and_stop (struct e1000_adapter*) ; 
 int /*<<< orphan*/  e1000_irq_disable (struct e1000_adapter*) ; 
 int /*<<< orphan*/  e1000_reset (struct e1000_adapter*) ; 
 int er32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ew32 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  napi_disable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  netif_carrier_off (struct net_device*) ; 
 int /*<<< orphan*/  netif_tx_disable (struct net_device*) ; 

void e1000_down(struct e1000_adapter *adapter)
{
	struct e1000_hw *hw = &adapter->hw;
	struct net_device *netdev = adapter->netdev;
	u32 rctl, tctl;

	/* disable receives in the hardware */
	rctl = er32(RCTL);
	ew32(RCTL, rctl & ~E1000_RCTL_EN);
	/* flush and sleep below */

	netif_tx_disable(netdev);

	/* disable transmits in the hardware */
	tctl = er32(TCTL);
	tctl &= ~E1000_TCTL_EN;
	ew32(TCTL, tctl);
	/* flush both disables and wait for them to finish */
	E1000_WRITE_FLUSH();
	msleep(10);

	/* Set the carrier off after transmits have been disabled in the
	 * hardware, to avoid race conditions with e1000_watchdog() (which
	 * may be running concurrently to us, checking for the carrier
	 * bit to decide whether it should enable transmits again). Such
	 * a race condition would result into transmission being disabled
	 * in the hardware until the next IFF_DOWN+IFF_UP cycle.
	 */
	netif_carrier_off(netdev);

	napi_disable(&adapter->napi);

	e1000_irq_disable(adapter);

	/* Setting DOWN must be after irq_disable to prevent
	 * a screaming interrupt.  Setting DOWN also prevents
	 * tasks from rescheduling.
	 */
	e1000_down_and_stop(adapter);

	adapter->link_speed = 0;
	adapter->link_duplex = 0;

	e1000_reset(adapter);
	e1000_clean_all_tx_rings(adapter);
	e1000_clean_all_rx_rings(adapter);
}