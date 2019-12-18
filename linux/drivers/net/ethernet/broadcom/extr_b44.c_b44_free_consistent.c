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
struct b44 {int flags; int /*<<< orphan*/ * tx_ring; int /*<<< orphan*/  tx_ring_dma; TYPE_1__* sdev; int /*<<< orphan*/ * rx_ring; int /*<<< orphan*/  rx_ring_dma; int /*<<< orphan*/ * tx_buffers; int /*<<< orphan*/ * rx_buffers; } ;
struct TYPE_2__ {int /*<<< orphan*/  dma_dev; } ;

/* Variables and functions */
 int B44_FLAG_RX_RING_HACK ; 
 int B44_FLAG_TX_RING_HACK ; 
 int /*<<< orphan*/  DMA_BIDIRECTIONAL ; 
 int /*<<< orphan*/  DMA_TABLE_BYTES ; 
 int /*<<< orphan*/  DMA_TO_DEVICE ; 
 int /*<<< orphan*/  dma_free_coherent (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_unmap_single (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void b44_free_consistent(struct b44 *bp)
{
	kfree(bp->rx_buffers);
	bp->rx_buffers = NULL;
	kfree(bp->tx_buffers);
	bp->tx_buffers = NULL;
	if (bp->rx_ring) {
		if (bp->flags & B44_FLAG_RX_RING_HACK) {
			dma_unmap_single(bp->sdev->dma_dev, bp->rx_ring_dma,
					 DMA_TABLE_BYTES, DMA_BIDIRECTIONAL);
			kfree(bp->rx_ring);
		} else
			dma_free_coherent(bp->sdev->dma_dev, DMA_TABLE_BYTES,
					  bp->rx_ring, bp->rx_ring_dma);
		bp->rx_ring = NULL;
		bp->flags &= ~B44_FLAG_RX_RING_HACK;
	}
	if (bp->tx_ring) {
		if (bp->flags & B44_FLAG_TX_RING_HACK) {
			dma_unmap_single(bp->sdev->dma_dev, bp->tx_ring_dma,
					 DMA_TABLE_BYTES, DMA_TO_DEVICE);
			kfree(bp->tx_ring);
		} else
			dma_free_coherent(bp->sdev->dma_dev, DMA_TABLE_BYTES,
					  bp->tx_ring, bp->tx_ring_dma);
		bp->tx_ring = NULL;
		bp->flags &= ~B44_FLAG_TX_RING_HACK;
	}
}