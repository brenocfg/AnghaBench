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
struct bnxt_tx_ring_info {scalar_t__ tx_cons; scalar_t__ tx_prod; } ;
struct bnxt_rx_ring_info {scalar_t__ rx_next_cons; scalar_t__ rx_sw_agg_prod; scalar_t__ rx_agg_prod; scalar_t__ rx_prod; } ;
struct bnxt_cp_ring_info {scalar_t__ cp_raw_cons; } ;
struct bnxt_napi {struct bnxt_rx_ring_info* rx_ring; struct bnxt_tx_ring_info* tx_ring; struct bnxt_cp_ring_info cp_ring; } ;
struct bnxt {int cp_nr_rings; struct bnxt_napi** bnapi; } ;

/* Variables and functions */

__attribute__((used)) static void bnxt_clear_ring_indices(struct bnxt *bp)
{
	int i;

	if (!bp->bnapi)
		return;

	for (i = 0; i < bp->cp_nr_rings; i++) {
		struct bnxt_napi *bnapi = bp->bnapi[i];
		struct bnxt_cp_ring_info *cpr;
		struct bnxt_rx_ring_info *rxr;
		struct bnxt_tx_ring_info *txr;

		if (!bnapi)
			continue;

		cpr = &bnapi->cp_ring;
		cpr->cp_raw_cons = 0;

		txr = bnapi->tx_ring;
		if (txr) {
			txr->tx_prod = 0;
			txr->tx_cons = 0;
		}

		rxr = bnapi->rx_ring;
		if (rxr) {
			rxr->rx_prod = 0;
			rxr->rx_agg_prod = 0;
			rxr->rx_sw_agg_prod = 0;
			rxr->rx_next_cons = 0;
		}
	}
}