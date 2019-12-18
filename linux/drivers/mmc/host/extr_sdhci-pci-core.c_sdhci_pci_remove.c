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
struct sdhci_pci_chip {int num_slots; int /*<<< orphan*/ * slots; scalar_t__ allow_runtime_pm; } ;
struct pci_dev {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 struct sdhci_pci_chip* pci_get_drvdata (struct pci_dev*) ; 
 int /*<<< orphan*/  sdhci_pci_remove_slot (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sdhci_pci_runtime_pm_forbid (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void sdhci_pci_remove(struct pci_dev *pdev)
{
	int i;
	struct sdhci_pci_chip *chip = pci_get_drvdata(pdev);

	if (chip->allow_runtime_pm)
		sdhci_pci_runtime_pm_forbid(&pdev->dev);

	for (i = 0; i < chip->num_slots; i++)
		sdhci_pci_remove_slot(chip->slots[i]);
}