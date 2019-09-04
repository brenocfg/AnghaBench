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
struct sk_buff {scalar_t__ len; } ;
struct net_device {int dummy; } ;
struct hisi_femac_queue {size_t tail; int num; struct sk_buff** skb; } ;
struct hisi_femac_priv {int tx_fifo_used_cnt; scalar_t__ port_base; struct hisi_femac_queue txq; } ;

/* Variables and functions */
 scalar_t__ ADDRQ_STAT ; 
 int TX_CNT_INUSE_MASK ; 
 int /*<<< orphan*/  dev_kfree_skb_any (struct sk_buff*) ; 
 int /*<<< orphan*/  hisi_femac_tx_dma_unmap (struct hisi_femac_priv*,struct sk_buff*,size_t) ; 
 int /*<<< orphan*/  netdev_completed_queue (struct net_device*,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  netdev_err (struct net_device*,char*,int,int) ; 
 struct hisi_femac_priv* netdev_priv (struct net_device*) ; 
 int netif_queue_stopped (struct net_device*) ; 
 int /*<<< orphan*/  netif_tx_lock (struct net_device*) ; 
 int /*<<< orphan*/  netif_tx_unlock (struct net_device*) ; 
 int /*<<< orphan*/  netif_wake_queue (struct net_device*) ; 
 int readl (scalar_t__) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static void hisi_femac_xmit_reclaim(struct net_device *dev)
{
	struct sk_buff *skb;
	struct hisi_femac_priv *priv = netdev_priv(dev);
	struct hisi_femac_queue *txq = &priv->txq;
	unsigned int bytes_compl = 0, pkts_compl = 0;
	u32 val;

	netif_tx_lock(dev);

	val = readl(priv->port_base + ADDRQ_STAT) & TX_CNT_INUSE_MASK;
	while (val < priv->tx_fifo_used_cnt) {
		skb = txq->skb[txq->tail];
		if (unlikely(!skb)) {
			netdev_err(dev, "xmitq_cnt_inuse=%d, tx_fifo_used=%d\n",
				   val, priv->tx_fifo_used_cnt);
			break;
		}
		hisi_femac_tx_dma_unmap(priv, skb, txq->tail);
		pkts_compl++;
		bytes_compl += skb->len;
		dev_kfree_skb_any(skb);

		priv->tx_fifo_used_cnt--;

		val = readl(priv->port_base + ADDRQ_STAT) & TX_CNT_INUSE_MASK;
		txq->skb[txq->tail] = NULL;
		txq->tail = (txq->tail + 1) % txq->num;
	}

	netdev_completed_queue(dev, pkts_compl, bytes_compl);

	if (unlikely(netif_queue_stopped(dev)) && pkts_compl)
		netif_wake_queue(dev);

	netif_tx_unlock(dev);
}