#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  tx_kicks; } ;
struct vector_private {int options; int /*<<< orphan*/  tx_poll; TYPE_2__* tx_queue; TYPE_1__ estats; int /*<<< orphan*/  coalesce; int /*<<< orphan*/  tl; int /*<<< orphan*/  dev; } ;
struct sk_buff {int /*<<< orphan*/  len; scalar_t__ xmit_more; } ;
struct net_device {int dummy; } ;
struct TYPE_5__ {int max_depth; } ;

/* Variables and functions */
 int NETDEV_TX_OK ; 
 int /*<<< orphan*/  TX_SMALL_PACKET ; 
 int VECTOR_TX ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct vector_private* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netdev_sent_queue (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netif_stop_queue (struct net_device*) ; 
 int /*<<< orphan*/  tasklet_schedule (int /*<<< orphan*/ *) ; 
 int vector_enqueue (TYPE_2__*,struct sk_buff*) ; 
 int /*<<< orphan*/  vector_send (TYPE_2__*) ; 
 int /*<<< orphan*/  writev_tx (struct vector_private*,struct sk_buff*) ; 

__attribute__((used)) static int vector_net_start_xmit(struct sk_buff *skb, struct net_device *dev)
{
	struct vector_private *vp = netdev_priv(dev);
	int queue_depth = 0;

	if ((vp->options & VECTOR_TX) == 0) {
		writev_tx(vp, skb);
		return NETDEV_TX_OK;
	}

	/* We do BQL only in the vector path, no point doing it in
	 * packet at a time mode as there is no device queue
	 */

	netdev_sent_queue(vp->dev, skb->len);
	queue_depth = vector_enqueue(vp->tx_queue, skb);

	/* if the device queue is full, stop the upper layers and
	 * flush it.
	 */

	if (queue_depth >= vp->tx_queue->max_depth - 1) {
		vp->estats.tx_kicks++;
		netif_stop_queue(dev);
		vector_send(vp->tx_queue);
		return NETDEV_TX_OK;
	}
	if (skb->xmit_more) {
		mod_timer(&vp->tl, vp->coalesce);
		return NETDEV_TX_OK;
	}
	if (skb->len < TX_SMALL_PACKET) {
		vp->estats.tx_kicks++;
		vector_send(vp->tx_queue);
	} else
		tasklet_schedule(&vp->tx_poll);
	return NETDEV_TX_OK;
}