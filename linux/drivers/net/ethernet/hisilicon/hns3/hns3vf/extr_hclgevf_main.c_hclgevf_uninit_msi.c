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
struct hclgevf_dev {int /*<<< orphan*/  vector_irq; int /*<<< orphan*/  vector_status; struct pci_dev* pdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  devm_kfree (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_free_irq_vectors (struct pci_dev*) ; 

__attribute__((used)) static void hclgevf_uninit_msi(struct hclgevf_dev *hdev)
{
	struct pci_dev *pdev = hdev->pdev;

	devm_kfree(&pdev->dev, hdev->vector_status);
	devm_kfree(&pdev->dev, hdev->vector_irq);
	pci_free_irq_vectors(pdev);
}