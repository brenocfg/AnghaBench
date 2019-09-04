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
struct tx_queue {int tx_bytes; scalar_t__ tx_desc_count; scalar_t__ tx_stop_threshold; int /*<<< orphan*/  tx_dropped; int /*<<< orphan*/  tx_packets; } ;
struct sk_buff {int len; } ;
struct netdev_queue {int dummy; } ;
struct net_device {int dummy; } ;
struct mv643xx_eth_private {struct tx_queue* txq; } ;
typedef  int /*<<< orphan*/  netdev_tx_t ;

/* Variables and functions */
 int /*<<< orphan*/  KERN_DEBUG ; 
 int /*<<< orphan*/  NETDEV_TX_BUSY ; 
 int /*<<< orphan*/  NETDEV_TX_OK ; 
 scalar_t__ __skb_linearize (struct sk_buff*) ; 
 int /*<<< orphan*/  dev_kfree_skb_any (struct sk_buff*) ; 
 scalar_t__ has_tiny_unaligned_frags (struct sk_buff*) ; 
 struct netdev_queue* netdev_get_tx_queue (struct net_device*,int) ; 
 int /*<<< orphan*/  netdev_printk (int /*<<< orphan*/ ,struct net_device*,char*) ; 
 struct mv643xx_eth_private* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_tx_stop_queue (struct netdev_queue*) ; 
 int skb_get_queue_mapping (struct sk_buff*) ; 
 scalar_t__ skb_is_gso (struct sk_buff*) ; 
 int txq_submit_skb (struct tx_queue*,struct sk_buff*,struct net_device*) ; 
 int txq_submit_tso (struct tx_queue*,struct sk_buff*,struct net_device*) ; 

__attribute__((used)) static netdev_tx_t mv643xx_eth_xmit(struct sk_buff *skb, struct net_device *dev)
{
	struct mv643xx_eth_private *mp = netdev_priv(dev);
	int length, queue, ret;
	struct tx_queue *txq;
	struct netdev_queue *nq;

	queue = skb_get_queue_mapping(skb);
	txq = mp->txq + queue;
	nq = netdev_get_tx_queue(dev, queue);

	if (has_tiny_unaligned_frags(skb) && __skb_linearize(skb)) {
		netdev_printk(KERN_DEBUG, dev,
			      "failed to linearize skb with tiny unaligned fragment\n");
		return NETDEV_TX_BUSY;
	}

	length = skb->len;

	if (skb_is_gso(skb))
		ret = txq_submit_tso(txq, skb, dev);
	else
		ret = txq_submit_skb(txq, skb, dev);
	if (!ret) {
		txq->tx_bytes += length;
		txq->tx_packets++;

		if (txq->tx_desc_count >= txq->tx_stop_threshold)
			netif_tx_stop_queue(nq);
	} else {
		txq->tx_dropped++;
		dev_kfree_skb_any(skb);
	}

	return NETDEV_TX_OK;
}