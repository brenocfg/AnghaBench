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
struct mtk_tx_dma {int dummy; } ;
struct mtk_eth {int /*<<< orphan*/  scratch_head; int /*<<< orphan*/ * rx_ring; scalar_t__ hwlro; int /*<<< orphan*/  rx_ring_qdma; scalar_t__ phy_scratch_ring; int /*<<< orphan*/ * scratch_ring; int /*<<< orphan*/  dev; scalar_t__* netdev; } ;

/* Variables and functions */
 int MTK_DMA_SIZE ; 
 int MTK_MAC_COUNT ; 
 int MTK_MAX_RX_RING_NUM ; 
 int /*<<< orphan*/  dma_free_coherent (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtk_hwlro_rx_uninit (struct mtk_eth*) ; 
 int /*<<< orphan*/  mtk_rx_clean (struct mtk_eth*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtk_tx_clean (struct mtk_eth*) ; 
 int /*<<< orphan*/  netdev_reset_queue (scalar_t__) ; 

__attribute__((used)) static void mtk_dma_free(struct mtk_eth *eth)
{
	int i;

	for (i = 0; i < MTK_MAC_COUNT; i++)
		if (eth->netdev[i])
			netdev_reset_queue(eth->netdev[i]);
	if (eth->scratch_ring) {
		dma_free_coherent(eth->dev,
				  MTK_DMA_SIZE * sizeof(struct mtk_tx_dma),
				  eth->scratch_ring,
				  eth->phy_scratch_ring);
		eth->scratch_ring = NULL;
		eth->phy_scratch_ring = 0;
	}
	mtk_tx_clean(eth);
	mtk_rx_clean(eth, &eth->rx_ring[0]);
	mtk_rx_clean(eth, &eth->rx_ring_qdma);

	if (eth->hwlro) {
		mtk_hwlro_rx_uninit(eth);
		for (i = 1; i < MTK_MAX_RX_RING_NUM; i++)
			mtk_rx_clean(eth, &eth->rx_ring[i]);
	}

	kfree(eth->scratch_head);
}