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
struct bnxt_ring_struct {int /*<<< orphan*/  ring_mem; } ;
struct bnxt_rx_ring_info {struct bnxt_ring_struct rx_agg_ring_struct; struct bnxt_ring_struct rx_ring_struct; int /*<<< orphan*/ * rx_agg_bmap; int /*<<< orphan*/ * page_pool; int /*<<< orphan*/  xdp_rxq; scalar_t__ xdp_prog; } ;
struct bnxt {int rx_nr_rings; struct bnxt_rx_ring_info* rx_ring; } ;

/* Variables and functions */
 int /*<<< orphan*/  bnxt_free_ring (struct bnxt*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bnxt_free_tpa_info (struct bnxt*) ; 
 int /*<<< orphan*/  bpf_prog_put (scalar_t__) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  page_pool_destroy (int /*<<< orphan*/ *) ; 
 scalar_t__ xdp_rxq_info_is_reg (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xdp_rxq_info_unreg (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void bnxt_free_rx_rings(struct bnxt *bp)
{
	int i;

	if (!bp->rx_ring)
		return;

	bnxt_free_tpa_info(bp);
	for (i = 0; i < bp->rx_nr_rings; i++) {
		struct bnxt_rx_ring_info *rxr = &bp->rx_ring[i];
		struct bnxt_ring_struct *ring;

		if (rxr->xdp_prog)
			bpf_prog_put(rxr->xdp_prog);

		if (xdp_rxq_info_is_reg(&rxr->xdp_rxq))
			xdp_rxq_info_unreg(&rxr->xdp_rxq);

		page_pool_destroy(rxr->page_pool);
		rxr->page_pool = NULL;

		kfree(rxr->rx_agg_bmap);
		rxr->rx_agg_bmap = NULL;

		ring = &rxr->rx_ring_struct;
		bnxt_free_ring(bp, &ring->ring_mem);

		ring = &rxr->rx_agg_ring_struct;
		bnxt_free_ring(bp, &ring->ring_mem);
	}
}