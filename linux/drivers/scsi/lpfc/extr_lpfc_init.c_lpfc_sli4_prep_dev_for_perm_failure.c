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
 int /*<<< orphan*/  lpfc_scsi_dev_block (struct lpfc_hba*) ; 
 int /*<<< orphan*/  lpfc_sli_flush_io_rings (struct lpfc_hba*) ; 
 int /*<<< orphan*/  lpfc_stop_hba_timers (struct lpfc_hba*) ; 

__attribute__((used)) static void
lpfc_sli4_prep_dev_for_perm_failure(struct lpfc_hba *phba)
{
	lpfc_printf_log(phba, KERN_ERR, LOG_INIT,
			"2827 PCI channel permanent disable for failure\n");

	/* Block all SCSI devices' I/Os on the host */
	lpfc_scsi_dev_block(phba);

	/* stop all timers */
	lpfc_stop_hba_timers(phba);

	/* Clean up all driver's outstanding I/Os */
	lpfc_sli_flush_io_rings(phba);
}