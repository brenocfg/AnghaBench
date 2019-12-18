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
struct mtk_rx_ring {int calc_idx_update; TYPE_1__* dma; int /*<<< orphan*/  dma_size; int /*<<< orphan*/  calc_idx; } ;
struct mtk_eth {struct mtk_rx_ring* rx_ring; int /*<<< orphan*/  hwlro; } ;
struct TYPE_2__ {int rxd2; } ;

/* Variables and functions */
 int MTK_MAX_RX_RING_NUM ; 
 int NEXT_DESP_IDX (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int RX_DMA_DONE ; 

__attribute__((used)) static struct mtk_rx_ring *mtk_get_rx_ring(struct mtk_eth *eth)
{
	int i;
	struct mtk_rx_ring *ring;
	int idx;

	if (!eth->hwlro)
		return &eth->rx_ring[0];

	for (i = 0; i < MTK_MAX_RX_RING_NUM; i++) {
		ring = &eth->rx_ring[i];
		idx = NEXT_DESP_IDX(ring->calc_idx, ring->dma_size);
		if (ring->dma[idx].rxd2 & RX_DMA_DONE) {
			ring->calc_idx_update = true;
			return ring;
		}
	}

	return NULL;
}