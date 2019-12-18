#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct meth_private {int /*<<< orphan*/  tx_ring_dma; int /*<<< orphan*/  tx_ring; TYPE_1__* pdev; int /*<<< orphan*/ ** tx_skbs; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  TX_RING_BUFFER_SIZE ; 
 int TX_RING_ENTRIES ; 
 int /*<<< orphan*/  dev_kfree_skb (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dma_free_coherent (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void meth_free_tx_ring(struct meth_private *priv)
{
	int i;

	/* Remove any pending skb */
	for (i = 0; i < TX_RING_ENTRIES; i++) {
		dev_kfree_skb(priv->tx_skbs[i]);
		priv->tx_skbs[i] = NULL;
	}
	dma_free_coherent(&priv->pdev->dev, TX_RING_BUFFER_SIZE, priv->tx_ring,
	                  priv->tx_ring_dma);
}