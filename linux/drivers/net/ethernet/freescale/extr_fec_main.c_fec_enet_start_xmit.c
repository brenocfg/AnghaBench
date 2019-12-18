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
struct sk_buff {int dummy; } ;
struct netdev_queue {int dummy; } ;
struct net_device {int dummy; } ;
struct fec_enet_private {struct fec_enet_priv_tx_q** tx_queue; } ;
struct fec_enet_priv_tx_q {int tx_stop_threshold; } ;
typedef  int netdev_tx_t ;

/* Variables and functions */
 int NETDEV_TX_OK ; 
 int fec_enet_get_free_txdesc_num (struct fec_enet_priv_tx_q*) ; 
 int fec_enet_txq_submit_skb (struct fec_enet_priv_tx_q*,struct sk_buff*,struct net_device*) ; 
 int fec_enet_txq_submit_tso (struct fec_enet_priv_tx_q*,struct sk_buff*,struct net_device*) ; 
 struct netdev_queue* netdev_get_tx_queue (struct net_device*,unsigned short) ; 
 struct fec_enet_private* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_tx_stop_queue (struct netdev_queue*) ; 
 unsigned short skb_get_queue_mapping (struct sk_buff*) ; 
 scalar_t__ skb_is_gso (struct sk_buff*) ; 

__attribute__((used)) static netdev_tx_t
fec_enet_start_xmit(struct sk_buff *skb, struct net_device *ndev)
{
	struct fec_enet_private *fep = netdev_priv(ndev);
	int entries_free;
	unsigned short queue;
	struct fec_enet_priv_tx_q *txq;
	struct netdev_queue *nq;
	int ret;

	queue = skb_get_queue_mapping(skb);
	txq = fep->tx_queue[queue];
	nq = netdev_get_tx_queue(ndev, queue);

	if (skb_is_gso(skb))
		ret = fec_enet_txq_submit_tso(txq, skb, ndev);
	else
		ret = fec_enet_txq_submit_skb(txq, skb, ndev);
	if (ret)
		return ret;

	entries_free = fec_enet_get_free_txdesc_num(txq);
	if (entries_free <= txq->tx_stop_threshold)
		netif_tx_stop_queue(nq);

	return NETDEV_TX_OK;
}