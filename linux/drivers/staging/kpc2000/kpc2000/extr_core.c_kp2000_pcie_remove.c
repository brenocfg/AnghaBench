#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  kobj; } ;
struct pci_dev {TYPE_1__ dev; } ;
struct kp2000_device {int /*<<< orphan*/  card_num; int /*<<< orphan*/  sem; TYPE_2__* pdev; int /*<<< orphan*/ * regs_bar_base; int /*<<< orphan*/ * dma_bar_base; } ;
struct TYPE_5__ {int /*<<< orphan*/  irq; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_BAR ; 
 int /*<<< orphan*/  PCARD_TO_DEV (struct kp2000_device*) ; 
 int /*<<< orphan*/  REG_BAR ; 
 int /*<<< orphan*/  card_num_ida ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct kp2000_device*) ; 
 int /*<<< orphan*/  ida_simple_remove (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iounmap (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct kp2000_device*) ; 
 int /*<<< orphan*/  kp2000_remove_cores (struct kp2000_device*) ; 
 int /*<<< orphan*/  kp_attr_list ; 
 int /*<<< orphan*/  mfd_remove_devices (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pci_disable_device (TYPE_2__*) ; 
 int /*<<< orphan*/  pci_disable_msi (TYPE_2__*) ; 
 struct kp2000_device* pci_get_drvdata (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_release_region (struct pci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_set_drvdata (struct pci_dev*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sysfs_remove_files (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void kp2000_pcie_remove(struct pci_dev *pdev)
{
	struct kp2000_device *pcard = pci_get_drvdata(pdev);

	if (!pcard)
		return;

	mutex_lock(&pcard->sem);
	kp2000_remove_cores(pcard);
	mfd_remove_devices(PCARD_TO_DEV(pcard));
	sysfs_remove_files(&pdev->dev.kobj, kp_attr_list);
	free_irq(pcard->pdev->irq, pcard);
	pci_disable_msi(pcard->pdev);
	if (pcard->dma_bar_base) {
		iounmap(pcard->dma_bar_base);
		pci_release_region(pdev, DMA_BAR);
		pcard->dma_bar_base = NULL;
	}
	if (pcard->regs_bar_base) {
		iounmap(pcard->regs_bar_base);
		pci_release_region(pdev, REG_BAR);
		pcard->regs_bar_base = NULL;
	}
	pci_disable_device(pcard->pdev);
	pci_set_drvdata(pdev, NULL);
	mutex_unlock(&pcard->sem);
	ida_simple_remove(&card_num_ida, pcard->card_num);
	kfree(pcard);
}