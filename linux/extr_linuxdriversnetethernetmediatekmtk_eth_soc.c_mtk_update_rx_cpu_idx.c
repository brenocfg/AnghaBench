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
struct mtk_rx_ring {int calc_idx_update; int /*<<< orphan*/  crx_idx_reg; int /*<<< orphan*/  calc_idx; } ;
struct mtk_eth {struct mtk_rx_ring* rx_ring; int /*<<< orphan*/  hwlro; } ;

/* Variables and functions */
 int MTK_MAX_RX_RING_NUM ; 
 int /*<<< orphan*/  mtk_w32 (struct mtk_eth*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void mtk_update_rx_cpu_idx(struct mtk_eth *eth)
{
	struct mtk_rx_ring *ring;
	int i;

	if (!eth->hwlro) {
		ring = &eth->rx_ring[0];
		mtk_w32(eth, ring->calc_idx, ring->crx_idx_reg);
	} else {
		for (i = 0; i < MTK_MAX_RX_RING_NUM; i++) {
			ring = &eth->rx_ring[i];
			if (ring->calc_idx_update) {
				ring->calc_idx_update = false;
				mtk_w32(eth, ring->calc_idx, ring->crx_idx_reg);
			}
		}
	}
}