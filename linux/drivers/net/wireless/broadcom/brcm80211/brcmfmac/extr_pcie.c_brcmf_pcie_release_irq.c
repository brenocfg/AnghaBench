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
typedef  int u32 ;
struct pci_dev {int /*<<< orphan*/  irq; int /*<<< orphan*/  dev; } ;
struct brcmf_pciedev_info {int irq_allocated; scalar_t__ in_irq; struct pci_dev* pdev; } ;
struct brcmf_bus {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BRCMF_PCIE_PCIE2REG_MAILBOXINT ; 
 int /*<<< orphan*/  brcmf_err (struct brcmf_bus*,char*) ; 
 int /*<<< orphan*/  brcmf_pcie_intr_disable (struct brcmf_pciedev_info*) ; 
 int brcmf_pcie_read_reg32 (struct brcmf_pciedev_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  brcmf_pcie_write_reg32 (struct brcmf_pciedev_info*,int /*<<< orphan*/ ,int) ; 
 struct brcmf_bus* dev_get_drvdata (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct brcmf_pciedev_info*) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  pci_disable_msi (struct pci_dev*) ; 

__attribute__((used)) static void brcmf_pcie_release_irq(struct brcmf_pciedev_info *devinfo)
{
	struct pci_dev *pdev = devinfo->pdev;
	struct brcmf_bus *bus = dev_get_drvdata(&pdev->dev);
	u32 status;
	u32 count;

	if (!devinfo->irq_allocated)
		return;

	brcmf_pcie_intr_disable(devinfo);
	free_irq(pdev->irq, devinfo);
	pci_disable_msi(pdev);

	msleep(50);
	count = 0;
	while ((devinfo->in_irq) && (count < 20)) {
		msleep(50);
		count++;
	}
	if (devinfo->in_irq)
		brcmf_err(bus, "Still in IRQ (processing) !!!\n");

	status = brcmf_pcie_read_reg32(devinfo, BRCMF_PCIE_PCIE2REG_MAILBOXINT);
	brcmf_pcie_write_reg32(devinfo, BRCMF_PCIE_PCIE2REG_MAILBOXINT, status);

	devinfo->irq_allocated = false;
}