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
struct bnxt_ring_struct {int nr_pages; void** pg_arr; int vmem_size; void** vmem; int /*<<< orphan*/  dma_arr; void* page_size; } ;
struct bnxt_tx_ring_info {int /*<<< orphan*/  tx_buf_ring; int /*<<< orphan*/  tx_desc_mapping; scalar_t__ tx_desc_ring; struct bnxt_ring_struct tx_ring_struct; } ;
struct bnxt_rx_ring_info {int /*<<< orphan*/  rx_agg_ring; int /*<<< orphan*/  rx_agg_desc_mapping; scalar_t__ rx_agg_desc_ring; struct bnxt_ring_struct rx_agg_ring_struct; int /*<<< orphan*/  rx_buf_ring; int /*<<< orphan*/  rx_desc_mapping; scalar_t__ rx_desc_ring; struct bnxt_ring_struct rx_ring_struct; } ;
struct bnxt_cp_ring_info {int /*<<< orphan*/  cp_desc_mapping; scalar_t__ cp_desc_ring; struct bnxt_ring_struct cp_ring_struct; } ;
struct bnxt_napi {struct bnxt_tx_ring_info* tx_ring; struct bnxt_rx_ring_info* rx_ring; struct bnxt_cp_ring_info cp_ring; } ;
struct bnxt {int cp_nr_rings; int cp_nr_pages; int rx_nr_pages; int rx_agg_nr_pages; int tx_nr_pages; struct bnxt_napi** bnapi; } ;

/* Variables and functions */
 void* HW_CMPD_RING_SIZE ; 
 void* HW_RXBD_RING_SIZE ; 
 int SW_RXBD_AGG_RING_SIZE ; 
 int SW_RXBD_RING_SIZE ; 
 int SW_TXBD_RING_SIZE ; 

__attribute__((used)) static void bnxt_init_ring_struct(struct bnxt *bp)
{
	int i;

	for (i = 0; i < bp->cp_nr_rings; i++) {
		struct bnxt_napi *bnapi = bp->bnapi[i];
		struct bnxt_cp_ring_info *cpr;
		struct bnxt_rx_ring_info *rxr;
		struct bnxt_tx_ring_info *txr;
		struct bnxt_ring_struct *ring;

		if (!bnapi)
			continue;

		cpr = &bnapi->cp_ring;
		ring = &cpr->cp_ring_struct;
		ring->nr_pages = bp->cp_nr_pages;
		ring->page_size = HW_CMPD_RING_SIZE;
		ring->pg_arr = (void **)cpr->cp_desc_ring;
		ring->dma_arr = cpr->cp_desc_mapping;
		ring->vmem_size = 0;

		rxr = bnapi->rx_ring;
		if (!rxr)
			goto skip_rx;

		ring = &rxr->rx_ring_struct;
		ring->nr_pages = bp->rx_nr_pages;
		ring->page_size = HW_RXBD_RING_SIZE;
		ring->pg_arr = (void **)rxr->rx_desc_ring;
		ring->dma_arr = rxr->rx_desc_mapping;
		ring->vmem_size = SW_RXBD_RING_SIZE * bp->rx_nr_pages;
		ring->vmem = (void **)&rxr->rx_buf_ring;

		ring = &rxr->rx_agg_ring_struct;
		ring->nr_pages = bp->rx_agg_nr_pages;
		ring->page_size = HW_RXBD_RING_SIZE;
		ring->pg_arr = (void **)rxr->rx_agg_desc_ring;
		ring->dma_arr = rxr->rx_agg_desc_mapping;
		ring->vmem_size = SW_RXBD_AGG_RING_SIZE * bp->rx_agg_nr_pages;
		ring->vmem = (void **)&rxr->rx_agg_ring;

skip_rx:
		txr = bnapi->tx_ring;
		if (!txr)
			continue;

		ring = &txr->tx_ring_struct;
		ring->nr_pages = bp->tx_nr_pages;
		ring->page_size = HW_RXBD_RING_SIZE;
		ring->pg_arr = (void **)txr->tx_desc_ring;
		ring->dma_arr = txr->tx_desc_mapping;
		ring->vmem_size = SW_TXBD_RING_SIZE * bp->tx_nr_pages;
		ring->vmem = (void **)&txr->tx_buf_ring;
	}
}