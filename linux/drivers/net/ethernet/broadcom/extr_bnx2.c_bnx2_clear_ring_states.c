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
struct bnx2_tx_ring_info {scalar_t__ hw_tx_cons; scalar_t__ tx_cons; } ;
struct bnx2_rx_ring_info {scalar_t__ rx_pg_cons; scalar_t__ rx_pg_prod; scalar_t__ rx_cons; scalar_t__ rx_prod; scalar_t__ rx_prod_bseq; } ;
struct bnx2_napi {struct bnx2_rx_ring_info rx_ring; struct bnx2_tx_ring_info tx_ring; } ;
struct bnx2 {struct bnx2_napi* bnx2_napi; } ;

/* Variables and functions */
 int BNX2_MAX_MSIX_VEC ; 

__attribute__((used)) static void
bnx2_clear_ring_states(struct bnx2 *bp)
{
	struct bnx2_napi *bnapi;
	struct bnx2_tx_ring_info *txr;
	struct bnx2_rx_ring_info *rxr;
	int i;

	for (i = 0; i < BNX2_MAX_MSIX_VEC; i++) {
		bnapi = &bp->bnx2_napi[i];
		txr = &bnapi->tx_ring;
		rxr = &bnapi->rx_ring;

		txr->tx_cons = 0;
		txr->hw_tx_cons = 0;
		rxr->rx_prod_bseq = 0;
		rxr->rx_prod = 0;
		rxr->rx_cons = 0;
		rxr->rx_pg_prod = 0;
		rxr->rx_pg_cons = 0;
	}
}