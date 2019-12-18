#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {TYPE_1__* hba_eq_hdl; } ;
struct lpfc_hba {int cfg_irq_chann; TYPE_2__ sli4_hba; TYPE_3__* pcidev; } ;
struct TYPE_7__ {int /*<<< orphan*/  irq; } ;
struct TYPE_5__ {int idx; struct lpfc_hba* phba; } ;

/* Variables and functions */
 int /*<<< orphan*/  KERN_INFO ; 
 int /*<<< orphan*/  KERN_WARNING ; 
 int /*<<< orphan*/  LOG_INIT ; 
 int /*<<< orphan*/  LPFC_DRIVER_NAME ; 
 int PCI_IRQ_AFFINITY ; 
 int PCI_IRQ_MSI ; 
 int /*<<< orphan*/  lpfc_printf_log (struct lpfc_hba*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  lpfc_sli4_intr_handler ; 
 int pci_alloc_irq_vectors (TYPE_3__*,int,int,int) ; 
 int /*<<< orphan*/  pci_free_irq_vectors (TYPE_3__*) ; 
 int request_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct lpfc_hba*) ; 

__attribute__((used)) static int
lpfc_sli4_enable_msi(struct lpfc_hba *phba)
{
	int rc, index;

	rc = pci_alloc_irq_vectors(phba->pcidev, 1, 1,
				   PCI_IRQ_MSI | PCI_IRQ_AFFINITY);
	if (rc > 0)
		lpfc_printf_log(phba, KERN_INFO, LOG_INIT,
				"0487 PCI enable MSI mode success.\n");
	else {
		lpfc_printf_log(phba, KERN_INFO, LOG_INIT,
				"0488 PCI enable MSI mode failed (%d)\n", rc);
		return rc ? rc : -1;
	}

	rc = request_irq(phba->pcidev->irq, lpfc_sli4_intr_handler,
			 0, LPFC_DRIVER_NAME, phba);
	if (rc) {
		pci_free_irq_vectors(phba->pcidev);
		lpfc_printf_log(phba, KERN_WARNING, LOG_INIT,
				"0490 MSI request_irq failed (%d)\n", rc);
		return rc;
	}

	for (index = 0; index < phba->cfg_irq_chann; index++) {
		phba->sli4_hba.hba_eq_hdl[index].idx = index;
		phba->sli4_hba.hba_eq_hdl[index].phba = phba;
	}

	return 0;
}