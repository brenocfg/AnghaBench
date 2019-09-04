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
typedef  int /*<<< orphan*/  u8 ;
struct bnx2_sw_bd {int /*<<< orphan*/ * data; } ;
struct bnx2_rx_ring_info {struct bnx2_sw_bd* rx_buf_ring; } ;
struct bnx2_napi {struct bnx2_rx_ring_info rx_ring; } ;
struct bnx2 {int num_rx_rings; int rx_max_ring_idx; int rx_max_pg_ring_idx; int /*<<< orphan*/  rx_buf_use_size; TYPE_1__* pdev; struct bnx2_napi* bnx2_napi; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  PCI_DMA_FROMDEVICE ; 
 int /*<<< orphan*/  bnx2_free_rx_page (struct bnx2*,struct bnx2_rx_ring_info*,int) ; 
 int /*<<< orphan*/  dma_unmap_addr (struct bnx2_sw_bd*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_unmap_single (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mapping ; 

__attribute__((used)) static void
bnx2_free_rx_skbs(struct bnx2 *bp)
{
	int i;

	for (i = 0; i < bp->num_rx_rings; i++) {
		struct bnx2_napi *bnapi = &bp->bnx2_napi[i];
		struct bnx2_rx_ring_info *rxr = &bnapi->rx_ring;
		int j;

		if (!rxr->rx_buf_ring)
			return;

		for (j = 0; j < bp->rx_max_ring_idx; j++) {
			struct bnx2_sw_bd *rx_buf = &rxr->rx_buf_ring[j];
			u8 *data = rx_buf->data;

			if (!data)
				continue;

			dma_unmap_single(&bp->pdev->dev,
					 dma_unmap_addr(rx_buf, mapping),
					 bp->rx_buf_use_size,
					 PCI_DMA_FROMDEVICE);

			rx_buf->data = NULL;

			kfree(data);
		}
		for (j = 0; j < bp->rx_max_pg_ring_idx; j++)
			bnx2_free_rx_page(bp, rxr, j);
	}
}