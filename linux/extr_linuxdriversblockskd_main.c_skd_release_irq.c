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
struct skd_device {int /*<<< orphan*/ * msix_entries; struct pci_dev* pdev; } ;
struct pci_dev {int /*<<< orphan*/  irq; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int SKD_MAX_MSIX_COUNT ; 
 int /*<<< orphan*/  devm_free_irq (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct skd_device*) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pci_free_irq_vectors (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_irq_vector (struct pci_dev*,int) ; 

__attribute__((used)) static void skd_release_irq(struct skd_device *skdev)
{
	struct pci_dev *pdev = skdev->pdev;

	if (skdev->msix_entries) {
		int i;

		for (i = 0; i < SKD_MAX_MSIX_COUNT; i++) {
			devm_free_irq(&pdev->dev, pci_irq_vector(pdev, i),
					skdev);
		}

		kfree(skdev->msix_entries);
		skdev->msix_entries = NULL;
	} else {
		devm_free_irq(&pdev->dev, pdev->irq, skdev);
	}

	pci_free_irq_vectors(pdev);
}