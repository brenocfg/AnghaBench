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
typedef  scalar_t__ uint32_t ;
struct pci_dev {scalar_t__ is_busmaster; } ;
struct lpfc_vport {struct lpfc_hba* phba; } ;
struct lpfc_hba {scalar_t__ intr_mode; int /*<<< orphan*/  worker_thread; int /*<<< orphan*/  brd_no; } ;
struct Scsi_Host {scalar_t__ hostdata; } ;

/* Variables and functions */
 int EIO ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  KERN_ERR ; 
 int /*<<< orphan*/  KERN_INFO ; 
 int /*<<< orphan*/  LOG_INIT ; 
 scalar_t__ LPFC_INTR_ERROR ; 
 int /*<<< orphan*/  PCI_D0 ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kthread_run (int /*<<< orphan*/ ,struct lpfc_hba*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lpfc_do_work ; 
 int /*<<< orphan*/  lpfc_log_intr_mode (struct lpfc_hba*,scalar_t__) ; 
 int /*<<< orphan*/  lpfc_online (struct lpfc_hba*) ; 
 int /*<<< orphan*/  lpfc_printf_log (struct lpfc_hba*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,...) ; 
 scalar_t__ lpfc_sli4_enable_intr (struct lpfc_hba*,scalar_t__) ; 
 int /*<<< orphan*/  lpfc_sli_brdrestart (struct lpfc_hba*) ; 
 struct Scsi_Host* pci_get_drvdata (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_restore_state (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_save_state (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_set_master (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_set_power_state (struct pci_dev*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
lpfc_pci_resume_one_s4(struct pci_dev *pdev)
{
	struct Scsi_Host *shost = pci_get_drvdata(pdev);
	struct lpfc_hba *phba = ((struct lpfc_vport *)shost->hostdata)->phba;
	uint32_t intr_mode;
	int error;

	lpfc_printf_log(phba, KERN_INFO, LOG_INIT,
			"0292 PCI device Power Management resume.\n");

	/* Restore device state from PCI config space */
	pci_set_power_state(pdev, PCI_D0);
	pci_restore_state(pdev);

	/*
	 * As the new kernel behavior of pci_restore_state() API call clears
	 * device saved_state flag, need to save the restored state again.
	 */
	pci_save_state(pdev);

	if (pdev->is_busmaster)
		pci_set_master(pdev);

	 /* Startup the kernel thread for this host adapter. */
	phba->worker_thread = kthread_run(lpfc_do_work, phba,
					"lpfc_worker_%d", phba->brd_no);
	if (IS_ERR(phba->worker_thread)) {
		error = PTR_ERR(phba->worker_thread);
		lpfc_printf_log(phba, KERN_ERR, LOG_INIT,
				"0293 PM resume failed to start worker "
				"thread: error=x%x.\n", error);
		return error;
	}

	/* Configure and enable interrupt */
	intr_mode = lpfc_sli4_enable_intr(phba, phba->intr_mode);
	if (intr_mode == LPFC_INTR_ERROR) {
		lpfc_printf_log(phba, KERN_ERR, LOG_INIT,
				"0294 PM resume Failed to enable interrupt\n");
		return -EIO;
	} else
		phba->intr_mode = intr_mode;

	/* Restart HBA and bring it online */
	lpfc_sli_brdrestart(phba);
	lpfc_online(phba);

	/* Log the current active interrupt mode */
	lpfc_log_intr_mode(phba, phba->intr_mode);

	return 0;
}