#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  unsigned int u16 ;
struct xenvif_rx_cb {scalar_t__ expires; } ;
struct xenvif_queue {int /*<<< orphan*/ * dealloc_task; int /*<<< orphan*/ * task; } ;
struct TYPE_4__ {scalar_t__ alg; } ;
struct xenvif {TYPE_3__* dev; TYPE_1__ hash; scalar_t__ drain_timeout; scalar_t__ multicast_control; struct xenvif_queue* queues; int /*<<< orphan*/  num_queues; } ;
struct sk_buff {scalar_t__ pkt_type; scalar_t__ data; struct net_device* dev; } ;
struct net_device {int dummy; } ;
struct ethhdr {int /*<<< orphan*/  h_dest; } ;
typedef  int /*<<< orphan*/  netdev_tx_t ;
struct TYPE_5__ {int /*<<< orphan*/  tx_dropped; } ;
struct TYPE_6__ {TYPE_2__ stats; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  NETDEV_TX_OK ; 
 scalar_t__ PACKET_MULTICAST ; 
 unsigned int READ_ONCE (int /*<<< orphan*/ ) ; 
 struct xenvif_rx_cb* XENVIF_RX_CB (struct sk_buff*) ; 
 scalar_t__ XEN_NETIF_CTRL_HASH_ALGORITHM_NONE ; 
 int /*<<< orphan*/  dev_kfree_skb (struct sk_buff*) ; 
 scalar_t__ jiffies ; 
 struct xenvif* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  pr_warn_ratelimited (char*,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_clear_hash (struct sk_buff*) ; 
 unsigned int skb_get_queue_mapping (struct sk_buff*) ; 
 int /*<<< orphan*/  xenvif_kick_thread (struct xenvif_queue*) ; 
 int /*<<< orphan*/  xenvif_mcast_match (struct xenvif*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xenvif_rx_queue_tail (struct xenvif_queue*,struct sk_buff*) ; 
 int /*<<< orphan*/  xenvif_schedulable (struct xenvif*) ; 

__attribute__((used)) static netdev_tx_t
xenvif_start_xmit(struct sk_buff *skb, struct net_device *dev)
{
	struct xenvif *vif = netdev_priv(dev);
	struct xenvif_queue *queue = NULL;
	unsigned int num_queues;
	u16 index;
	struct xenvif_rx_cb *cb;

	BUG_ON(skb->dev != dev);

	/* Drop the packet if queues are not set up.
	 * This handler should be called inside an RCU read section
	 * so we don't need to enter it here explicitly.
	 */
	num_queues = READ_ONCE(vif->num_queues);
	if (num_queues < 1)
		goto drop;

	/* Obtain the queue to be used to transmit this packet */
	index = skb_get_queue_mapping(skb);
	if (index >= num_queues) {
		pr_warn_ratelimited("Invalid queue %hu for packet on interface %s\n",
				    index, vif->dev->name);
		index %= num_queues;
	}
	queue = &vif->queues[index];

	/* Drop the packet if queue is not ready */
	if (queue->task == NULL ||
	    queue->dealloc_task == NULL ||
	    !xenvif_schedulable(vif))
		goto drop;

	if (vif->multicast_control && skb->pkt_type == PACKET_MULTICAST) {
		struct ethhdr *eth = (struct ethhdr *)skb->data;

		if (!xenvif_mcast_match(vif, eth->h_dest))
			goto drop;
	}

	cb = XENVIF_RX_CB(skb);
	cb->expires = jiffies + vif->drain_timeout;

	/* If there is no hash algorithm configured then make sure there
	 * is no hash information in the socket buffer otherwise it
	 * would be incorrectly forwarded to the frontend.
	 */
	if (vif->hash.alg == XEN_NETIF_CTRL_HASH_ALGORITHM_NONE)
		skb_clear_hash(skb);

	xenvif_rx_queue_tail(queue, skb);
	xenvif_kick_thread(queue);

	return NETDEV_TX_OK;

 drop:
	vif->dev->stats.tx_dropped++;
	dev_kfree_skb(skb);
	return NETDEV_TX_OK;
}