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
typedef  size_t u32 ;
struct stmmac_rx_queue {scalar_t__ page_pool; int /*<<< orphan*/  buf_pool; int /*<<< orphan*/  dma_rx_phy; int /*<<< orphan*/  dma_erx; int /*<<< orphan*/  dma_rx; } ;
struct stmmac_priv {int /*<<< orphan*/  device; int /*<<< orphan*/  extend_desc; struct stmmac_rx_queue* rx_queue; TYPE_1__* plat; } ;
struct dma_extended_desc {int dummy; } ;
struct dma_desc {int dummy; } ;
struct TYPE_2__ {size_t rx_queues_to_use; } ;

/* Variables and functions */
 int DMA_RX_SIZE ; 
 int /*<<< orphan*/  dma_free_coherent (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_free_rx_skbufs (struct stmmac_priv*,size_t) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  page_pool_destroy (scalar_t__) ; 
 int /*<<< orphan*/  page_pool_request_shutdown (scalar_t__) ; 

__attribute__((used)) static void free_dma_rx_desc_resources(struct stmmac_priv *priv)
{
	u32 rx_count = priv->plat->rx_queues_to_use;
	u32 queue;

	/* Free RX queue resources */
	for (queue = 0; queue < rx_count; queue++) {
		struct stmmac_rx_queue *rx_q = &priv->rx_queue[queue];

		/* Release the DMA RX socket buffers */
		dma_free_rx_skbufs(priv, queue);

		/* Free DMA regions of consistent memory previously allocated */
		if (!priv->extend_desc)
			dma_free_coherent(priv->device,
					  DMA_RX_SIZE * sizeof(struct dma_desc),
					  rx_q->dma_rx, rx_q->dma_rx_phy);
		else
			dma_free_coherent(priv->device, DMA_RX_SIZE *
					  sizeof(struct dma_extended_desc),
					  rx_q->dma_erx, rx_q->dma_rx_phy);

		kfree(rx_q->buf_pool);
		if (rx_q->page_pool) {
			page_pool_request_shutdown(rx_q->page_pool);
			page_pool_destroy(rx_q->page_pool);
		}
	}
}