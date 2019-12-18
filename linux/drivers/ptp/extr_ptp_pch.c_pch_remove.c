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
struct pci_dev {scalar_t__ irq; int /*<<< orphan*/  dev; } ;
struct pch_dev {scalar_t__ mem_base; int /*<<< orphan*/  mem_size; int /*<<< orphan*/ * regs; int /*<<< orphan*/  ptp_clock; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  free_irq (scalar_t__,struct pch_dev*) ; 
 int /*<<< orphan*/  iounmap (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct pch_dev*) ; 
 int /*<<< orphan*/  pci_disable_device (struct pci_dev*) ; 
 struct pch_dev* pci_get_drvdata (struct pci_dev*) ; 
 int /*<<< orphan*/  ptp_clock_unregister (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  release_mem_region (scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void pch_remove(struct pci_dev *pdev)
{
	struct pch_dev *chip = pci_get_drvdata(pdev);

	ptp_clock_unregister(chip->ptp_clock);
	/* free the interrupt */
	if (pdev->irq != 0)
		free_irq(pdev->irq, chip);

	/* unmap the virtual IO memory space */
	if (chip->regs != NULL) {
		iounmap(chip->regs);
		chip->regs = NULL;
	}
	/* release the reserved IO memory space */
	if (chip->mem_base != 0) {
		release_mem_region(chip->mem_base, chip->mem_size);
		chip->mem_base = 0;
	}
	pci_disable_device(pdev);
	kfree(chip);
	dev_info(&pdev->dev, "complete\n");
}