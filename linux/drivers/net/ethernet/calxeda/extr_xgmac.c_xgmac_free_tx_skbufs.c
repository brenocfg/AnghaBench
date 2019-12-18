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
struct xgmac_priv {int /*<<< orphan*/ ** tx_skbuff; int /*<<< orphan*/  device; struct xgmac_dma_desc* dma_tx; } ;
struct xgmac_dma_desc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_TO_DEVICE ; 
 int DMA_TX_RING_SZ ; 
 int /*<<< orphan*/  desc_get_buf_addr (struct xgmac_dma_desc*) ; 
 int /*<<< orphan*/  desc_get_buf_len (struct xgmac_dma_desc*) ; 
 scalar_t__ desc_get_tx_fs (struct xgmac_dma_desc*) ; 
 scalar_t__ desc_get_tx_ls (struct xgmac_dma_desc*) ; 
 int /*<<< orphan*/  dev_kfree_skb_any (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dma_unmap_page (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_unmap_single (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void xgmac_free_tx_skbufs(struct xgmac_priv *priv)
{
	int i;
	struct xgmac_dma_desc *p;

	if (!priv->tx_skbuff)
		return;

	for (i = 0; i < DMA_TX_RING_SZ; i++) {
		if (priv->tx_skbuff[i] == NULL)
			continue;

		p = priv->dma_tx + i;
		if (desc_get_tx_fs(p))
			dma_unmap_single(priv->device, desc_get_buf_addr(p),
					 desc_get_buf_len(p), DMA_TO_DEVICE);
		else
			dma_unmap_page(priv->device, desc_get_buf_addr(p),
				       desc_get_buf_len(p), DMA_TO_DEVICE);

		if (desc_get_tx_ls(p))
			dev_kfree_skb_any(priv->tx_skbuff[i]);
		priv->tx_skbuff[i] = NULL;
	}
}