#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct sk_buff {scalar_t__ protocol; TYPE_2__* dev; } ;
struct TYPE_5__ {int /*<<< orphan*/  lock; } ;
struct ipvl_port {TYPE_1__ backlog; int /*<<< orphan*/  wq; } ;
struct TYPE_7__ {int tx_pkt; } ;
struct TYPE_6__ {int /*<<< orphan*/  rx_dropped; } ;

/* Variables and functions */
 int /*<<< orphan*/  ETH_P_PAUSE ; 
 scalar_t__ IPVLAN_QBACKLOG_LIMIT ; 
 TYPE_4__* IPVL_SKB_CB (struct sk_buff*) ; 
 int /*<<< orphan*/  __skb_queue_tail (TYPE_1__*,struct sk_buff*) ; 
 int /*<<< orphan*/  atomic_long_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_hold (TYPE_2__*) ; 
 scalar_t__ htons (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 
 scalar_t__ skb_queue_len (TYPE_1__*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ipvlan_multicast_enqueue(struct ipvl_port *port,
				     struct sk_buff *skb, bool tx_pkt)
{
	if (skb->protocol == htons(ETH_P_PAUSE)) {
		kfree_skb(skb);
		return;
	}

	/* Record that the deferred packet is from TX or RX path. By
	 * looking at mac-addresses on packet will lead to erronus decisions.
	 * (This would be true for a loopback-mode on master device or a
	 * hair-pin mode of the switch.)
	 */
	IPVL_SKB_CB(skb)->tx_pkt = tx_pkt;

	spin_lock(&port->backlog.lock);
	if (skb_queue_len(&port->backlog) < IPVLAN_QBACKLOG_LIMIT) {
		if (skb->dev)
			dev_hold(skb->dev);
		__skb_queue_tail(&port->backlog, skb);
		spin_unlock(&port->backlog.lock);
		schedule_work(&port->wq);
	} else {
		spin_unlock(&port->backlog.lock);
		atomic_long_inc(&skb->dev->rx_dropped);
		kfree_skb(skb);
	}
}