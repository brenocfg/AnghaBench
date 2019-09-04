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
struct xgmac_priv {struct sk_buff** rx_skbuff; scalar_t__ dma_buf_sz; int /*<<< orphan*/  device; struct xgmac_dma_desc* dma_rx; } ;
struct xgmac_dma_desc {int dummy; } ;
struct sk_buff {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_FROM_DEVICE ; 
 int DMA_RX_RING_SZ ; 
 scalar_t__ NET_IP_ALIGN ; 
 int /*<<< orphan*/  desc_get_buf_addr (struct xgmac_dma_desc*) ; 
 int /*<<< orphan*/  dev_kfree_skb_any (struct sk_buff*) ; 
 int /*<<< orphan*/  dma_unmap_single (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void xgmac_free_rx_skbufs(struct xgmac_priv *priv)
{
	int i;
	struct xgmac_dma_desc *p;

	if (!priv->rx_skbuff)
		return;

	for (i = 0; i < DMA_RX_RING_SZ; i++) {
		struct sk_buff *skb = priv->rx_skbuff[i];
		if (skb == NULL)
			continue;

		p = priv->dma_rx + i;
		dma_unmap_single(priv->device, desc_get_buf_addr(p),
				 priv->dma_buf_sz - NET_IP_ALIGN, DMA_FROM_DEVICE);
		dev_kfree_skb_any(skb);
		priv->rx_skbuff[i] = NULL;
	}
}