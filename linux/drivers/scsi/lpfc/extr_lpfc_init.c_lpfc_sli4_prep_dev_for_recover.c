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
struct lpfc_hba {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  KERN_ERR ; 
 int /*<<< orphan*/  LOG_INIT ; 
 int /*<<< orphan*/  lpfc_printf_log (struct lpfc_hba*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  lpfc_sli_abort_fcp_rings (struct lpfc_hba*) ; 

__attribute__((used)) static void
lpfc_sli4_prep_dev_for_recover(struct lpfc_hba *phba)
{
	lpfc_printf_log(phba, KERN_ERR, LOG_INIT,
			"2828 PCI channel I/O abort preparing for recovery\n");
	/*
	 * There may be errored I/Os through HBA, abort all I/Os on txcmplq
	 * and let the SCSI mid-layer to retry them to recover.
	 */
	lpfc_sli_abort_fcp_rings(phba);
}