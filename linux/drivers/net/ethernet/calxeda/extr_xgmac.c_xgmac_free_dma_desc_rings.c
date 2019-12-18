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
struct xgmac_priv {int /*<<< orphan*/ * tx_skbuff; int /*<<< orphan*/ * rx_skbuff; int /*<<< orphan*/ * dma_rx; int /*<<< orphan*/  dma_rx_phy; int /*<<< orphan*/  device; int /*<<< orphan*/ * dma_tx; int /*<<< orphan*/  dma_tx_phy; } ;
struct xgmac_dma_desc {int dummy; } ;

/* Variables and functions */
 int DMA_RX_RING_SZ ; 
 int DMA_TX_RING_SZ ; 
 int /*<<< orphan*/  dma_free_coherent (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xgmac_free_rx_skbufs (struct xgmac_priv*) ; 
 int /*<<< orphan*/  xgmac_free_tx_skbufs (struct xgmac_priv*) ; 

__attribute__((used)) static void xgmac_free_dma_desc_rings(struct xgmac_priv *priv)
{
	/* Release the DMA TX/RX socket buffers */
	xgmac_free_rx_skbufs(priv);
	xgmac_free_tx_skbufs(priv);

	/* Free the consistent memory allocated for descriptor rings */
	if (priv->dma_tx) {
		dma_free_coherent(priv->device,
				  DMA_TX_RING_SZ * sizeof(struct xgmac_dma_desc),
				  priv->dma_tx, priv->dma_tx_phy);
		priv->dma_tx = NULL;
	}
	if (priv->dma_rx) {
		dma_free_coherent(priv->device,
				  DMA_RX_RING_SZ * sizeof(struct xgmac_dma_desc),
				  priv->dma_rx, priv->dma_rx_phy);
		priv->dma_rx = NULL;
	}
	kfree(priv->rx_skbuff);
	priv->rx_skbuff = NULL;
	kfree(priv->tx_skbuff);
	priv->tx_skbuff = NULL;
}