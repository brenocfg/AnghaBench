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
struct meth_private {int /*<<< orphan*/ * rx_skbs; scalar_t__* rx_ring_dmas; scalar_t__* rx_ring; TYPE_1__* pdev; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_FROM_DEVICE ; 
 int /*<<< orphan*/  METH_RX_BUFF_SIZE ; 
 int RX_RING_ENTRIES ; 
 int /*<<< orphan*/  dma_unmap_single (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree_skb (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void meth_free_rx_ring(struct meth_private *priv)
{
	int i;

	for (i = 0; i < RX_RING_ENTRIES; i++) {
		dma_unmap_single(&priv->pdev->dev, priv->rx_ring_dmas[i],
				 METH_RX_BUFF_SIZE, DMA_FROM_DEVICE);
		priv->rx_ring[i] = 0;
		priv->rx_ring_dmas[i] = 0;
		kfree_skb(priv->rx_skbs[i]);
	}
}