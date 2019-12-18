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
struct rtl8169_private {int /*<<< orphan*/  napi; scalar_t__ RxDescArray; struct net_device* dev; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int NUM_RX_DESC ; 
 int /*<<< orphan*/  napi_disable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  napi_enable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  netif_stop_queue (struct net_device*) ; 
 int /*<<< orphan*/  netif_wake_queue (struct net_device*) ; 
 int /*<<< orphan*/  rtl8169_hw_reset (struct rtl8169_private*) ; 
 int /*<<< orphan*/  rtl8169_init_ring_indexes (struct rtl8169_private*) ; 
 int /*<<< orphan*/  rtl8169_mark_to_asic (scalar_t__) ; 
 int /*<<< orphan*/  rtl8169_tx_clear (struct rtl8169_private*) ; 
 int /*<<< orphan*/  rtl_hw_start (struct rtl8169_private*) ; 
 int /*<<< orphan*/  synchronize_rcu () ; 

__attribute__((used)) static void rtl_reset_work(struct rtl8169_private *tp)
{
	struct net_device *dev = tp->dev;
	int i;

	napi_disable(&tp->napi);
	netif_stop_queue(dev);
	synchronize_rcu();

	rtl8169_hw_reset(tp);

	for (i = 0; i < NUM_RX_DESC; i++)
		rtl8169_mark_to_asic(tp->RxDescArray + i);

	rtl8169_tx_clear(tp);
	rtl8169_init_ring_indexes(tp);

	napi_enable(&tp->napi);
	rtl_hw_start(tp);
	netif_wake_queue(dev);
}