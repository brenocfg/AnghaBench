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
struct TYPE_4__ {int /*<<< orphan*/  lock; } ;
struct xenvif_queue {scalar_t__ rx_queue_len; scalar_t__ rx_queue_max; TYPE_2__ rx_queue; int /*<<< orphan*/  id; TYPE_1__* vif; } ;
struct sk_buff {scalar_t__ len; } ;
struct net_device {int dummy; } ;
struct TYPE_3__ {struct net_device* dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  __skb_queue_tail (TYPE_2__*,struct sk_buff*) ; 
 int /*<<< orphan*/  netdev_get_tx_queue (struct net_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netif_tx_stop_queue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

void xenvif_rx_queue_tail(struct xenvif_queue *queue, struct sk_buff *skb)
{
	unsigned long flags;

	spin_lock_irqsave(&queue->rx_queue.lock, flags);

	__skb_queue_tail(&queue->rx_queue, skb);

	queue->rx_queue_len += skb->len;
	if (queue->rx_queue_len > queue->rx_queue_max) {
		struct net_device *dev = queue->vif->dev;

		netif_tx_stop_queue(netdev_get_tx_queue(dev, queue->id));
	}

	spin_unlock_irqrestore(&queue->rx_queue.lock, flags);
}