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
struct bnxt {int flags; int /*<<< orphan*/  vnic_info; } ;

/* Variables and functions */
 int BNXT_FLAG_CHIP_P5 ; 
 int BNXT_FLAG_TPA ; 
 int /*<<< orphan*/  bnxt_hwrm_clear_vnic_filter (struct bnxt*) ; 
 int /*<<< orphan*/  bnxt_hwrm_clear_vnic_rss (struct bnxt*) ; 
 int /*<<< orphan*/  bnxt_hwrm_vnic_ctx_free (struct bnxt*) ; 
 int /*<<< orphan*/  bnxt_hwrm_vnic_free (struct bnxt*) ; 
 int /*<<< orphan*/  bnxt_set_tpa (struct bnxt*,int) ; 

__attribute__((used)) static void bnxt_clear_vnic(struct bnxt *bp)
{
	if (!bp->vnic_info)
		return;

	bnxt_hwrm_clear_vnic_filter(bp);
	if (!(bp->flags & BNXT_FLAG_CHIP_P5)) {
		/* clear all RSS setting before free vnic ctx */
		bnxt_hwrm_clear_vnic_rss(bp);
		bnxt_hwrm_vnic_ctx_free(bp);
	}
	/* before free the vnic, undo the vnic tpa settings */
	if (bp->flags & BNXT_FLAG_TPA)
		bnxt_set_tpa(bp, false);
	bnxt_hwrm_vnic_free(bp);
	if (bp->flags & BNXT_FLAG_CHIP_P5)
		bnxt_hwrm_vnic_ctx_free(bp);
}