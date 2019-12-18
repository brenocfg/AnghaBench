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
typedef  int /*<<< orphan*/  u8 ;
struct net_local {TYPE_2__* deferred_skb; } ;
struct TYPE_3__ {int /*<<< orphan*/  tx_bytes; int /*<<< orphan*/  tx_packets; } ;
struct net_device {TYPE_1__ stats; } ;
struct TYPE_4__ {scalar_t__ len; scalar_t__ data; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_consume_skb_irq (TYPE_2__*) ; 
 struct net_local* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_trans_update (struct net_device*) ; 
 int /*<<< orphan*/  netif_wake_queue (struct net_device*) ; 
 scalar_t__ xemaclite_send_data (struct net_local*,int /*<<< orphan*/ *,scalar_t__) ; 

__attribute__((used)) static void xemaclite_tx_handler(struct net_device *dev)
{
	struct net_local *lp = netdev_priv(dev);

	dev->stats.tx_packets++;

	if (!lp->deferred_skb)
		return;

	if (xemaclite_send_data(lp, (u8 *)lp->deferred_skb->data,
				lp->deferred_skb->len))
		return;

	dev->stats.tx_bytes += lp->deferred_skb->len;
	dev_consume_skb_irq(lp->deferred_skb);
	lp->deferred_skb = NULL;
	netif_trans_update(dev); /* prevent tx timeout */
	netif_wake_queue(dev);
}