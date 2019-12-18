#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct pci_dev {int /*<<< orphan*/  dev; } ;
struct TYPE_6__ {int /*<<< orphan*/  dma; int /*<<< orphan*/  va; int /*<<< orphan*/  size; } ;
struct TYPE_7__ {TYPE_2__ mbox_mem_alloced; } ;
struct TYPE_5__ {int /*<<< orphan*/  boot_kset; } ;
struct beiscsi_hba {int /*<<< orphan*/  shost; TYPE_4__* pcidev; TYPE_3__ ctrl; int /*<<< orphan*/  wq; TYPE_1__ boot_struct; int /*<<< orphan*/  sess_work; int /*<<< orphan*/  recover_port; int /*<<< orphan*/  hw_check; } ;
struct TYPE_8__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  beiscsi_disable_port (struct beiscsi_hba*,int) ; 
 int /*<<< orphan*/  beiscsi_free_mem (struct beiscsi_hba*) ; 
 int /*<<< orphan*/  beiscsi_iface_destroy_default (struct beiscsi_hba*) ; 
 int /*<<< orphan*/  beiscsi_unmap_pci_function (struct beiscsi_hba*) ; 
 int /*<<< orphan*/  cancel_delayed_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cancel_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  del_timer_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  destroy_workqueue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  dma_free_coherent (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iscsi_boot_destroy_kset (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iscsi_host_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iscsi_host_remove (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_dev_put (TYPE_4__*) ; 
 int /*<<< orphan*/  pci_disable_device (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_disable_pcie_error_reporting (struct pci_dev*) ; 
 struct beiscsi_hba* pci_get_drvdata (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_release_regions (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_set_drvdata (struct pci_dev*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void beiscsi_remove(struct pci_dev *pcidev)
{
	struct beiscsi_hba *phba = NULL;

	phba = pci_get_drvdata(pcidev);
	if (!phba) {
		dev_err(&pcidev->dev, "beiscsi_remove called with no phba\n");
		return;
	}

	/* first stop UE detection before unloading */
	del_timer_sync(&phba->hw_check);
	cancel_delayed_work_sync(&phba->recover_port);
	cancel_work_sync(&phba->sess_work);

	beiscsi_iface_destroy_default(phba);
	iscsi_host_remove(phba->shost);
	beiscsi_disable_port(phba, 1);

	/* after cancelling boot_work */
	iscsi_boot_destroy_kset(phba->boot_struct.boot_kset);

	/* free all resources */
	destroy_workqueue(phba->wq);
	beiscsi_free_mem(phba);

	/* ctrl uninit */
	beiscsi_unmap_pci_function(phba);
	dma_free_coherent(&phba->pcidev->dev,
			    phba->ctrl.mbox_mem_alloced.size,
			    phba->ctrl.mbox_mem_alloced.va,
			    phba->ctrl.mbox_mem_alloced.dma);

	pci_dev_put(phba->pcidev);
	iscsi_host_free(phba->shost);
	pci_disable_pcie_error_reporting(pcidev);
	pci_set_drvdata(pcidev, NULL);
	pci_release_regions(pcidev);
	pci_disable_device(pcidev);
}