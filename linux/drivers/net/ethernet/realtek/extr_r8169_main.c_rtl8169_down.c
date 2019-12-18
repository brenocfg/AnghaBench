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
struct rtl8169_private {int /*<<< orphan*/  napi; int /*<<< orphan*/  phydev; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  napi_disable (int /*<<< orphan*/ *) ; 
 struct rtl8169_private* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_stop_queue (struct net_device*) ; 
 int /*<<< orphan*/  phy_stop (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtl8169_hw_reset (struct rtl8169_private*) ; 
 int /*<<< orphan*/  rtl8169_rx_clear (struct rtl8169_private*) ; 
 int /*<<< orphan*/  rtl8169_rx_missed (struct net_device*) ; 
 int /*<<< orphan*/  rtl8169_tx_clear (struct rtl8169_private*) ; 
 int /*<<< orphan*/  rtl_pll_power_down (struct rtl8169_private*) ; 
 int /*<<< orphan*/  synchronize_rcu () ; 

__attribute__((used)) static void rtl8169_down(struct net_device *dev)
{
	struct rtl8169_private *tp = netdev_priv(dev);

	phy_stop(tp->phydev);

	napi_disable(&tp->napi);
	netif_stop_queue(dev);

	rtl8169_hw_reset(tp);
	/*
	 * At this point device interrupts can not be enabled in any function,
	 * as netif_running is not true (rtl8169_interrupt, rtl8169_reset_task)
	 * and napi is disabled (rtl8169_poll).
	 */
	rtl8169_rx_missed(dev);

	/* Give a racing hard_start_xmit a few cycles to complete. */
	synchronize_rcu();

	rtl8169_tx_clear(tp);

	rtl8169_rx_clear(tp);

	rtl_pll_power_down(tp);
}