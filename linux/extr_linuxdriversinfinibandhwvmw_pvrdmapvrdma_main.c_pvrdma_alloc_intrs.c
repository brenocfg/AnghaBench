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
struct pvrdma_dev {int nr_vectors; struct pci_dev* pdev; } ;
struct pci_dev {int /*<<< orphan*/  dev; scalar_t__ msix_enabled; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRV_NAME ; 
 int /*<<< orphan*/  IRQF_SHARED ; 
 int PCI_IRQ_LEGACY ; 
 int PCI_IRQ_MSI ; 
 int PCI_IRQ_MSIX ; 
 int PVRDMA_MAX_INTERRUPTS ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct pvrdma_dev*) ; 
 int pci_alloc_irq_vectors (struct pci_dev*,int,int,int) ; 
 int /*<<< orphan*/  pci_free_irq_vectors (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_irq_vector (struct pci_dev*,int) ; 
 int /*<<< orphan*/  pvrdma_intr0_handler ; 
 int /*<<< orphan*/  pvrdma_intr1_handler ; 
 int /*<<< orphan*/  pvrdma_intrx_handler ; 
 int request_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct pvrdma_dev*) ; 

__attribute__((used)) static int pvrdma_alloc_intrs(struct pvrdma_dev *dev)
{
	struct pci_dev *pdev = dev->pdev;
	int ret = 0, i;

	ret = pci_alloc_irq_vectors(pdev, 1, PVRDMA_MAX_INTERRUPTS,
			PCI_IRQ_MSIX);
	if (ret < 0) {
		ret = pci_alloc_irq_vectors(pdev, 1, 1,
				PCI_IRQ_MSI | PCI_IRQ_LEGACY);
		if (ret < 0)
			return ret;
	}
	dev->nr_vectors = ret;

	ret = request_irq(pci_irq_vector(dev->pdev, 0), pvrdma_intr0_handler,
			pdev->msix_enabled ? 0 : IRQF_SHARED, DRV_NAME, dev);
	if (ret) {
		dev_err(&dev->pdev->dev,
			"failed to request interrupt 0\n");
		goto out_free_vectors;
	}

	for (i = 1; i < dev->nr_vectors; i++) {
		ret = request_irq(pci_irq_vector(dev->pdev, i),
				i == 1 ? pvrdma_intr1_handler :
					 pvrdma_intrx_handler,
				0, DRV_NAME, dev);
		if (ret) {
			dev_err(&dev->pdev->dev,
				"failed to request interrupt %d\n", i);
			goto free_irqs;
		}
	}

	return 0;

free_irqs:
	while (--i >= 0)
		free_irq(pci_irq_vector(dev->pdev, i), dev);
out_free_vectors:
	pci_free_irq_vectors(pdev);
	return ret;
}