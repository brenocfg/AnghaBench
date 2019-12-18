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
struct bnxt {int /*<<< orphan*/ * bnapi; int /*<<< orphan*/ * rx_ring; int /*<<< orphan*/ * tx_ring; int /*<<< orphan*/ * tx_ring_map; } ;

/* Variables and functions */
 int /*<<< orphan*/  bnxt_clear_ring_indices (struct bnxt*) ; 
 int /*<<< orphan*/  bnxt_free_cp_rings (struct bnxt*) ; 
 int /*<<< orphan*/  bnxt_free_ntp_fltrs (struct bnxt*,int) ; 
 int /*<<< orphan*/  bnxt_free_ring_grps (struct bnxt*) ; 
 int /*<<< orphan*/  bnxt_free_ring_stats (struct bnxt*) ; 
 int /*<<< orphan*/  bnxt_free_rx_rings (struct bnxt*) ; 
 int /*<<< orphan*/  bnxt_free_tx_rings (struct bnxt*) ; 
 int /*<<< orphan*/  bnxt_free_vnic_attributes (struct bnxt*) ; 
 int /*<<< orphan*/  bnxt_free_vnics (struct bnxt*) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void bnxt_free_mem(struct bnxt *bp, bool irq_re_init)
{
	bnxt_free_vnic_attributes(bp);
	bnxt_free_tx_rings(bp);
	bnxt_free_rx_rings(bp);
	bnxt_free_cp_rings(bp);
	bnxt_free_ntp_fltrs(bp, irq_re_init);
	if (irq_re_init) {
		bnxt_free_ring_stats(bp);
		bnxt_free_ring_grps(bp);
		bnxt_free_vnics(bp);
		kfree(bp->tx_ring_map);
		bp->tx_ring_map = NULL;
		kfree(bp->tx_ring);
		bp->tx_ring = NULL;
		kfree(bp->rx_ring);
		bp->rx_ring = NULL;
		kfree(bp->bnapi);
		bp->bnapi = NULL;
	} else {
		bnxt_clear_ring_indices(bp);
	}
}