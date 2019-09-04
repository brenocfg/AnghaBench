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
struct pci_dev {int dummy; } ;
struct hsu_dma_chip {int /*<<< orphan*/  irq; } ;

/* Variables and functions */
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct hsu_dma_chip*) ; 
 int /*<<< orphan*/  hsu_dma_remove (struct hsu_dma_chip*) ; 
 struct hsu_dma_chip* pci_get_drvdata (struct pci_dev*) ; 

__attribute__((used)) static void hsu_pci_remove(struct pci_dev *pdev)
{
	struct hsu_dma_chip *chip = pci_get_drvdata(pdev);

	free_irq(chip->irq, chip);
	hsu_dma_remove(chip);
}