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
struct lpfc_hba {int /*<<< orphan*/  pcidev; } ;

/* Variables and functions */
 int /*<<< orphan*/  KERN_ERR ; 
 int /*<<< orphan*/  LOG_INIT ; 
 int /*<<< orphan*/  LPFC_MBX_WAIT ; 
 int /*<<< orphan*/  lpfc_block_mgmt_io (struct lpfc_hba*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lpfc_printf_log (struct lpfc_hba*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  lpfc_scsi_dev_block (struct lpfc_hba*) ; 
 int /*<<< orphan*/  lpfc_sli_disable_intr (struct lpfc_hba*) ; 
 int /*<<< orphan*/  lpfc_sli_flush_io_rings (struct lpfc_hba*) ; 
 int /*<<< orphan*/  lpfc_stop_hba_timers (struct lpfc_hba*) ; 
 int /*<<< orphan*/  pci_disable_device (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
lpfc_sli_prep_dev_for_reset(struct lpfc_hba *phba)
{
	lpfc_printf_log(phba, KERN_ERR, LOG_INIT,
			"2710 PCI channel disable preparing for reset\n");

	/* Block any management I/Os to the device */
	lpfc_block_mgmt_io(phba, LPFC_MBX_WAIT);

	/* Block all SCSI devices' I/Os on the host */
	lpfc_scsi_dev_block(phba);

	/* Flush all driver's outstanding SCSI I/Os as we are to reset */
	lpfc_sli_flush_io_rings(phba);

	/* stop all timers */
	lpfc_stop_hba_timers(phba);

	/* Disable interrupt and pci device */
	lpfc_sli_disable_intr(phba);
	pci_disable_device(phba->pcidev);
}