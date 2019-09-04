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
struct ftgmac100_txdes {int dummy; } ;
struct ftgmac100_rxdes {int dummy; } ;
struct ftgmac100 {int /*<<< orphan*/  rx_scratch_dma; int /*<<< orphan*/ * rx_scratch; int /*<<< orphan*/  dev; int /*<<< orphan*/ * txdes; int /*<<< orphan*/  txdes_dma; int /*<<< orphan*/ * rxdes; int /*<<< orphan*/  rxdes_dma; int /*<<< orphan*/  tx_skbs; int /*<<< orphan*/  rx_skbs; } ;

/* Variables and functions */
 int MAX_RX_QUEUE_ENTRIES ; 
 int MAX_TX_QUEUE_ENTRIES ; 
 int RX_BUF_SIZE ; 
 int /*<<< orphan*/  dma_free_coherent (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ftgmac100_free_rings(struct ftgmac100 *priv)
{
	/* Free skb arrays */
	kfree(priv->rx_skbs);
	kfree(priv->tx_skbs);

	/* Free descriptors */
	if (priv->rxdes)
		dma_free_coherent(priv->dev, MAX_RX_QUEUE_ENTRIES *
				  sizeof(struct ftgmac100_rxdes),
				  priv->rxdes, priv->rxdes_dma);
	priv->rxdes = NULL;

	if (priv->txdes)
		dma_free_coherent(priv->dev, MAX_TX_QUEUE_ENTRIES *
				  sizeof(struct ftgmac100_txdes),
				  priv->txdes, priv->txdes_dma);
	priv->txdes = NULL;

	/* Free scratch packet buffer */
	if (priv->rx_scratch)
		dma_free_coherent(priv->dev, RX_BUF_SIZE,
				  priv->rx_scratch, priv->rx_scratch_dma);
}