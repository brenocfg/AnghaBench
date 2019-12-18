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
struct lpfc_hba {int cfg_hdw_queue; } ;

/* Variables and functions */
 int /*<<< orphan*/  DUMP_ELS ; 
 int /*<<< orphan*/  DUMP_IO ; 
 int /*<<< orphan*/  DUMP_MBX ; 
 int /*<<< orphan*/  DUMP_NVMELS ; 
 int /*<<< orphan*/  lpfc_debug_dump_cq (struct lpfc_hba*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  lpfc_debug_dump_dat_rq (struct lpfc_hba*) ; 
 int /*<<< orphan*/  lpfc_debug_dump_hba_eq (struct lpfc_hba*,int) ; 
 int /*<<< orphan*/  lpfc_debug_dump_hdr_rq (struct lpfc_hba*) ; 
 int /*<<< orphan*/  lpfc_debug_dump_wq (struct lpfc_hba*,int /*<<< orphan*/ ,int) ; 

void
lpfc_debug_dump_all_queues(struct lpfc_hba *phba)
{
	int idx;

	/*
	 * Dump Work Queues (WQs)
	 */
	lpfc_debug_dump_wq(phba, DUMP_MBX, 0);
	lpfc_debug_dump_wq(phba, DUMP_ELS, 0);
	lpfc_debug_dump_wq(phba, DUMP_NVMELS, 0);

	for (idx = 0; idx < phba->cfg_hdw_queue; idx++)
		lpfc_debug_dump_wq(phba, DUMP_IO, idx);

	lpfc_debug_dump_hdr_rq(phba);
	lpfc_debug_dump_dat_rq(phba);
	/*
	 * Dump Complete Queues (CQs)
	 */
	lpfc_debug_dump_cq(phba, DUMP_MBX, 0);
	lpfc_debug_dump_cq(phba, DUMP_ELS, 0);
	lpfc_debug_dump_cq(phba, DUMP_NVMELS, 0);

	for (idx = 0; idx < phba->cfg_hdw_queue; idx++)
		lpfc_debug_dump_cq(phba, DUMP_IO, idx);

	/*
	 * Dump Event Queues (EQs)
	 */
	for (idx = 0; idx < phba->cfg_hdw_queue; idx++)
		lpfc_debug_dump_hba_eq(phba, idx);
}