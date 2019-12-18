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
struct mtk_tx_ring {int /*<<< orphan*/ * dma_pdma; int /*<<< orphan*/  phys_pdma; int /*<<< orphan*/ * dma; int /*<<< orphan*/  phys; int /*<<< orphan*/ * buf; } ;
struct mtk_eth {int /*<<< orphan*/  dev; struct mtk_tx_ring tx_ring; } ;

/* Variables and functions */
 int MTK_DMA_SIZE ; 
 int /*<<< orphan*/  dma_free_coherent (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtk_tx_unmap (struct mtk_eth*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void mtk_tx_clean(struct mtk_eth *eth)
{
	struct mtk_tx_ring *ring = &eth->tx_ring;
	int i;

	if (ring->buf) {
		for (i = 0; i < MTK_DMA_SIZE; i++)
			mtk_tx_unmap(eth, &ring->buf[i]);
		kfree(ring->buf);
		ring->buf = NULL;
	}

	if (ring->dma) {
		dma_free_coherent(eth->dev,
				  MTK_DMA_SIZE * sizeof(*ring->dma),
				  ring->dma,
				  ring->phys);
		ring->dma = NULL;
	}

	if (ring->dma_pdma) {
		dma_free_coherent(eth->dev,
				  MTK_DMA_SIZE * sizeof(*ring->dma_pdma),
				  ring->dma_pdma,
				  ring->phys_pdma);
		ring->dma_pdma = NULL;
	}
}