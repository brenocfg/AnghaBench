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
typedef  size_t u32 ;
struct sk_buff {int dummy; } ;
struct hisi_femac_queue {size_t tail; size_t head; size_t num; struct sk_buff** skb; int /*<<< orphan*/ * dma_phys; } ;
struct hisi_femac_priv {scalar_t__ tx_fifo_used_cnt; int /*<<< orphan*/  ndev; int /*<<< orphan*/  dev; struct hisi_femac_queue rxq; struct hisi_femac_queue txq; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_FROM_DEVICE ; 
 int /*<<< orphan*/  MAX_FRAME_SIZE ; 
 int /*<<< orphan*/  dev_kfree_skb_any (struct sk_buff*) ; 
 int /*<<< orphan*/  dma_unmap_single (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hisi_femac_tx_dma_unmap (struct hisi_femac_priv*,struct sk_buff*,size_t) ; 
 int /*<<< orphan*/  netdev_err (int /*<<< orphan*/ ,char*,size_t,size_t) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static void hisi_femac_free_skb_rings(struct hisi_femac_priv *priv)
{
	struct hisi_femac_queue *txq = &priv->txq;
	struct hisi_femac_queue *rxq = &priv->rxq;
	struct sk_buff *skb;
	dma_addr_t dma_addr;
	u32 pos;

	pos = rxq->tail;
	while (pos != rxq->head) {
		skb = rxq->skb[pos];
		if (unlikely(!skb)) {
			netdev_err(priv->ndev, "NULL rx skb. pos=%d, head=%d\n",
				   pos, rxq->head);
			continue;
		}

		dma_addr = rxq->dma_phys[pos];
		dma_unmap_single(priv->dev, dma_addr, MAX_FRAME_SIZE,
				 DMA_FROM_DEVICE);

		dev_kfree_skb_any(skb);
		rxq->skb[pos] = NULL;
		pos = (pos + 1) % rxq->num;
	}
	rxq->tail = pos;

	pos = txq->tail;
	while (pos != txq->head) {
		skb = txq->skb[pos];
		if (unlikely(!skb)) {
			netdev_err(priv->ndev, "NULL tx skb. pos=%d, head=%d\n",
				   pos, txq->head);
			continue;
		}
		hisi_femac_tx_dma_unmap(priv, skb, pos);
		dev_kfree_skb_any(skb);
		txq->skb[pos] = NULL;
		pos = (pos + 1) % txq->num;
	}
	txq->tail = pos;
	priv->tx_fifo_used_cnt = 0;
}