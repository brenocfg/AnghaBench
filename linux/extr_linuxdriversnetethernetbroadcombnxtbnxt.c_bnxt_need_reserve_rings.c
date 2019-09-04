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
struct bnxt_hw_resc {scalar_t__ resv_tx_rings; int resv_rx_rings; int resv_cp_rings; int resv_hw_ring_grps; int resv_vnics; } ;
struct bnxt {int rx_nr_rings; int hwrm_spec_code; scalar_t__ tx_nr_rings; int flags; struct bnxt_hw_resc hw_resc; } ;

/* Variables and functions */
 int BNXT_FLAG_AGG_RINGS ; 
 int BNXT_FLAG_RFS ; 
 scalar_t__ BNXT_NEW_RM (struct bnxt*) ; 
 int bnxt_cp_rings_in_use (struct bnxt*) ; 

__attribute__((used)) static bool bnxt_need_reserve_rings(struct bnxt *bp)
{
	struct bnxt_hw_resc *hw_resc = &bp->hw_resc;
	int cp = bnxt_cp_rings_in_use(bp);
	int rx = bp->rx_nr_rings;
	int vnic = 1, grp = rx;

	if (bp->hwrm_spec_code < 0x10601)
		return false;

	if (hw_resc->resv_tx_rings != bp->tx_nr_rings)
		return true;

	if (bp->flags & BNXT_FLAG_RFS)
		vnic = rx + 1;
	if (bp->flags & BNXT_FLAG_AGG_RINGS)
		rx <<= 1;
	if (BNXT_NEW_RM(bp) &&
	    (hw_resc->resv_rx_rings != rx || hw_resc->resv_cp_rings != cp ||
	     hw_resc->resv_hw_ring_grps != grp || hw_resc->resv_vnics != vnic))
		return true;
	return false;
}