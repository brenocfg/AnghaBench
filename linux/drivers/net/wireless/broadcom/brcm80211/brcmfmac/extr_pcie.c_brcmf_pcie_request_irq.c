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
struct pci_dev {int /*<<< orphan*/  irq; int /*<<< orphan*/  dev; } ;
struct brcmf_pciedev_info {int irq_allocated; struct pci_dev* pdev; } ;
struct brcmf_bus {int dummy; } ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  IRQF_SHARED ; 
 int /*<<< orphan*/  PCIE ; 
 int /*<<< orphan*/  brcmf_dbg (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  brcmf_err (struct brcmf_bus*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  brcmf_pcie_intr_disable (struct brcmf_pciedev_info*) ; 
 int /*<<< orphan*/  brcmf_pcie_isr_thread ; 
 int /*<<< orphan*/  brcmf_pcie_quick_check_isr ; 
 struct brcmf_bus* dev_get_drvdata (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pci_disable_msi (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_enable_msi (struct pci_dev*) ; 
 scalar_t__ request_threaded_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,struct brcmf_pciedev_info*) ; 

__attribute__((used)) static int brcmf_pcie_request_irq(struct brcmf_pciedev_info *devinfo)
{
	struct pci_dev *pdev = devinfo->pdev;
	struct brcmf_bus *bus = dev_get_drvdata(&pdev->dev);

	brcmf_pcie_intr_disable(devinfo);

	brcmf_dbg(PCIE, "Enter\n");

	pci_enable_msi(pdev);
	if (request_threaded_irq(pdev->irq, brcmf_pcie_quick_check_isr,
				 brcmf_pcie_isr_thread, IRQF_SHARED,
				 "brcmf_pcie_intr", devinfo)) {
		pci_disable_msi(pdev);
		brcmf_err(bus, "Failed to request IRQ %d\n", pdev->irq);
		return -EIO;
	}
	devinfo->irq_allocated = true;
	return 0;
}