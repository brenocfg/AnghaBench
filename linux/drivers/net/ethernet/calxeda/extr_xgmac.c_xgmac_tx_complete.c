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
struct xgmac_priv {unsigned int tx_tail; int /*<<< orphan*/  dev; struct sk_buff** tx_skbuff; int /*<<< orphan*/  device; int /*<<< orphan*/  tx_head; struct xgmac_dma_desc* dma_tx; } ;
struct xgmac_dma_desc {int dummy; } ;
struct sk_buff {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_TO_DEVICE ; 
 int /*<<< orphan*/  DMA_TX_RING_SZ ; 
 scalar_t__ MAX_SKB_FRAGS ; 
 int /*<<< orphan*/  desc_get_buf_addr (struct xgmac_dma_desc*) ; 
 int /*<<< orphan*/  desc_get_buf_len (struct xgmac_dma_desc*) ; 
 scalar_t__ desc_get_owner (struct xgmac_dma_desc*) ; 
 scalar_t__ desc_get_tx_fs (struct xgmac_dma_desc*) ; 
 scalar_t__ desc_get_tx_ls (struct xgmac_dma_desc*) ; 
 int /*<<< orphan*/  desc_get_tx_status (struct xgmac_priv*,struct xgmac_dma_desc*) ; 
 int /*<<< orphan*/  dev_consume_skb_any (struct sk_buff*) ; 
 scalar_t__ dma_ring_cnt (int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ) ; 
 unsigned int dma_ring_incr (unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_unmap_page (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_unmap_single (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netdev_dbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,unsigned int) ; 
 scalar_t__ netif_queue_stopped (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netif_wake_queue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smp_mb () ; 
 scalar_t__ tx_dma_ring_space (struct xgmac_priv*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static void xgmac_tx_complete(struct xgmac_priv *priv)
{
	while (dma_ring_cnt(priv->tx_head, priv->tx_tail, DMA_TX_RING_SZ)) {
		unsigned int entry = priv->tx_tail;
		struct sk_buff *skb = priv->tx_skbuff[entry];
		struct xgmac_dma_desc *p = priv->dma_tx + entry;

		/* Check if the descriptor is owned by the DMA. */
		if (desc_get_owner(p))
			break;

		netdev_dbg(priv->dev, "tx ring: curr %d, dirty %d\n",
			priv->tx_head, priv->tx_tail);

		if (desc_get_tx_fs(p))
			dma_unmap_single(priv->device, desc_get_buf_addr(p),
					 desc_get_buf_len(p), DMA_TO_DEVICE);
		else
			dma_unmap_page(priv->device, desc_get_buf_addr(p),
				       desc_get_buf_len(p), DMA_TO_DEVICE);

		/* Check tx error on the last segment */
		if (desc_get_tx_ls(p)) {
			desc_get_tx_status(priv, p);
			dev_consume_skb_any(skb);
		}

		priv->tx_skbuff[entry] = NULL;
		priv->tx_tail = dma_ring_incr(entry, DMA_TX_RING_SZ);
	}

	/* Ensure tx_tail is visible to xgmac_xmit */
	smp_mb();
	if (unlikely(netif_queue_stopped(priv->dev) &&
	    (tx_dma_ring_space(priv) > MAX_SKB_FRAGS)))
		netif_wake_queue(priv->dev);
}