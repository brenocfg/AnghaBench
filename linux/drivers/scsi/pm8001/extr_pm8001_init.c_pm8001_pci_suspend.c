#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct sas_ha_struct {struct pm8001_hba_info* lldd_ha; } ;
struct pm8001_hba_info {int number_of_intr; scalar_t__ chip_id; int /*<<< orphan*/  name; int /*<<< orphan*/ * tasklet; int /*<<< orphan*/  irq; struct sas_ha_struct* irq_vector; int /*<<< orphan*/  shost; } ;
struct pci_dev {int /*<<< orphan*/  msix_cap; int /*<<< orphan*/  dev; int /*<<< orphan*/  pm_cap; } ;
typedef  int /*<<< orphan*/  pm_message_t ;
struct TYPE_2__ {int /*<<< orphan*/  (* chip_soft_rst ) (struct pm8001_hba_info*) ;int /*<<< orphan*/  (* interrupt_disable ) (struct pm8001_hba_info*,int) ;} ;

/* Variables and functions */
 int ENODEV ; 
 TYPE_1__* PM8001_CHIP_DISP ; 
 int PM8001_MAX_MSIX_VEC ; 
 scalar_t__ chip_8001 ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  flush_workqueue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct sas_ha_struct*) ; 
 int /*<<< orphan*/  pci_choose_state (struct pci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_disable_device (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_free_irq_vectors (struct pci_dev*) ; 
 struct sas_ha_struct* pci_get_drvdata (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_irq_vector (struct pci_dev*,int) ; 
 int /*<<< orphan*/  pci_msi_enabled () ; 
 int /*<<< orphan*/  pci_save_state (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_set_power_state (struct pci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm8001_printk (char*,struct pci_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm8001_wq ; 
 int /*<<< orphan*/  sas_suspend_ha (struct sas_ha_struct*) ; 
 int /*<<< orphan*/  scsi_block_requests (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct pm8001_hba_info*,int) ; 
 int /*<<< orphan*/  stub2 (struct pm8001_hba_info*) ; 
 int /*<<< orphan*/  synchronize_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tasklet_kill (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int pm8001_pci_suspend(struct pci_dev *pdev, pm_message_t state)
{
	struct sas_ha_struct *sha = pci_get_drvdata(pdev);
	struct pm8001_hba_info *pm8001_ha;
	int  i, j;
	u32 device_state;
	pm8001_ha = sha->lldd_ha;
	sas_suspend_ha(sha);
	flush_workqueue(pm8001_wq);
	scsi_block_requests(pm8001_ha->shost);
	if (!pdev->pm_cap) {
		dev_err(&pdev->dev, " PCI PM not supported\n");
		return -ENODEV;
	}
	PM8001_CHIP_DISP->interrupt_disable(pm8001_ha, 0xFF);
	PM8001_CHIP_DISP->chip_soft_rst(pm8001_ha);
#ifdef PM8001_USE_MSIX
	for (i = 0; i < pm8001_ha->number_of_intr; i++)
		synchronize_irq(pci_irq_vector(pdev, i));
	for (i = 0; i < pm8001_ha->number_of_intr; i++)
		free_irq(pci_irq_vector(pdev, i), &pm8001_ha->irq_vector[i]);
	pci_free_irq_vectors(pdev);
#else
	free_irq(pm8001_ha->irq, sha);
#endif
#ifdef PM8001_USE_TASKLET
	/* For non-msix and msix interrupts */
	if ((!pdev->msix_cap || !pci_msi_enabled()) ||
	    (pm8001_ha->chip_id == chip_8001))
		tasklet_kill(&pm8001_ha->tasklet[0]);
	else
		for (j = 0; j < PM8001_MAX_MSIX_VEC; j++)
			tasklet_kill(&pm8001_ha->tasklet[j]);
#endif
	device_state = pci_choose_state(pdev, state);
	pm8001_printk("pdev=0x%p, slot=%s, entering "
		      "operating state [D%d]\n", pdev,
		      pm8001_ha->name, device_state);
	pci_save_state(pdev);
	pci_disable_device(pdev);
	pci_set_power_state(pdev, device_state);
	return 0;
}