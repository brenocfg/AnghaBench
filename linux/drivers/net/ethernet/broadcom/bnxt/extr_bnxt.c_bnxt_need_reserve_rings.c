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
struct bnxt_hw_resc {scalar_t__ resv_tx_rings; int resv_rx_rings; int resv_cp_rings; int resv_vnics; int resv_stat_ctxs; int resv_hw_ring_grps; int resv_irqs; } ;
struct bnxt {int rx_nr_rings; int hwrm_spec_code; scalar_t__ tx_nr_rings; int flags; struct bnxt_hw_resc hw_resc; } ;

/* Variables and functions */
 int BNXT_FLAG_AGG_RINGS ; 
 int BNXT_FLAG_CHIP_P5 ; 
 int BNXT_FLAG_RFS ; 
 scalar_t__ BNXT_NEW_RM (struct bnxt*) ; 
 scalar_t__ BNXT_PF (struct bnxt*) ; 
 int bnxt_cp_rings_in_use (struct bnxt*) ; 
 int bnxt_get_func_stat_ctxs (struct bnxt*) ; 
 int bnxt_nq_rings_in_use (struct bnxt*) ; 

__attribute__((used)) static bool bnxt_need_reserve_rings(struct bnxt *bp)
{
	struct bnxt_hw_resc *hw_resc = &bp->hw_resc;
	int cp = bnxt_cp_rings_in_use(bp);
	int nq = bnxt_nq_rings_in_use(bp);
	int rx = bp->rx_nr_rings, stat;
	int vnic = 1, grp = rx;

	if (bp->hwrm_spec_code < 0x10601)
		return false;

	if (hw_resc->resv_tx_rings != bp->tx_nr_rings)
		return true;

	if ((bp->flags & BNXT_FLAG_RFS) && !(bp->flags & BNXT_FLAG_CHIP_P5))
		vnic = rx + 1;
	if (bp->flags & BNXT_FLAG_AGG_RINGS)
		rx <<= 1;
	stat = bnxt_get_func_stat_ctxs(bp);
	if (BNXT_NEW_RM(bp) &&
	    (hw_resc->resv_rx_rings != rx || hw_resc->resv_cp_rings != cp ||
	     hw_resc->resv_vnics != vnic || hw_resc->resv_stat_ctxs != stat ||
	     (hw_resc->resv_hw_ring_grps != grp &&
	      !(bp->flags & BNXT_FLAG_CHIP_P5))))
		return true;
	if ((bp->flags & BNXT_FLAG_CHIP_P5) && BNXT_PF(bp) &&
	    hw_resc->resv_irqs != nq)
		return true;
	return false;
}