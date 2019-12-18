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
typedef  scalar_t__ u32 ;
struct lpfc_hba {scalar_t__ cfg_hdw_queue; } ;

/* Variables and functions */
 int /*<<< orphan*/  lpfc_adjust_high_watermark (struct lpfc_hba*,scalar_t__) ; 
 int /*<<< orphan*/  lpfc_adjust_pvt_pool_count (struct lpfc_hba*,scalar_t__) ; 
 int /*<<< orphan*/  lpfc_snapshot_mxp (struct lpfc_hba*,scalar_t__) ; 

__attribute__((used)) static void lpfc_hb_mxp_handler(struct lpfc_hba *phba)
{
	u32 i;
	u32 hwq_count;

	hwq_count = phba->cfg_hdw_queue;
	for (i = 0; i < hwq_count; i++) {
		/* Adjust XRIs in private pool */
		lpfc_adjust_pvt_pool_count(phba, i);

		/* Adjust high watermark */
		lpfc_adjust_high_watermark(phba, i);

#ifdef LPFC_MXP_STAT
		/* Snapshot pbl, pvt and busy count */
		lpfc_snapshot_mxp(phba, i);
#endif
	}
}