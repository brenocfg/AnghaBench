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
struct pci_dev {int /*<<< orphan*/  dev; } ;
struct hinic_hwif {void* cfg_regs_bar; void* intr_regs_base; struct pci_dev* pdev; } ;

/* Variables and functions */
 int ENOMEM ; 
 scalar_t__ HINIC_IS_PF (struct hinic_hwif*) ; 
 int /*<<< orphan*/  HINIC_PCI_CFG_REGS_BAR ; 
 int /*<<< orphan*/  HINIC_PCI_INTR_REGS_BAR ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  dma_attr_init (struct hinic_hwif*) ; 
 int hwif_ready (struct hinic_hwif*) ; 
 int /*<<< orphan*/  iounmap (void*) ; 
 void* pci_ioremap_bar (struct pci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  read_hwif_attr (struct hinic_hwif*) ; 
 int /*<<< orphan*/  set_ppf (struct hinic_hwif*) ; 

int hinic_init_hwif(struct hinic_hwif *hwif, struct pci_dev *pdev)
{
	int err;

	hwif->pdev = pdev;

	hwif->cfg_regs_bar = pci_ioremap_bar(pdev, HINIC_PCI_CFG_REGS_BAR);
	if (!hwif->cfg_regs_bar) {
		dev_err(&pdev->dev, "Failed to map configuration regs\n");
		return -ENOMEM;
	}

	hwif->intr_regs_base = pci_ioremap_bar(pdev, HINIC_PCI_INTR_REGS_BAR);
	if (!hwif->intr_regs_base) {
		dev_err(&pdev->dev, "Failed to map configuration regs\n");
		err = -ENOMEM;
		goto err_map_intr_bar;
	}

	err = hwif_ready(hwif);
	if (err) {
		dev_err(&pdev->dev, "HW interface is not ready\n");
		goto err_hwif_ready;
	}

	read_hwif_attr(hwif);

	if (HINIC_IS_PF(hwif))
		set_ppf(hwif);

	/* No transactionss before DMA is initialized */
	dma_attr_init(hwif);
	return 0;

err_hwif_ready:
	iounmap(hwif->intr_regs_base);

err_map_intr_bar:
	iounmap(hwif->cfg_regs_bar);

	return err;
}