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
struct pci_endpoint_test {int num_irqs; struct pci_dev* pdev; } ;
struct device {int dummy; } ;
struct pci_dev {struct device dev; } ;

/* Variables and functions */
#define  IRQ_TYPE_LEGACY 130 
#define  IRQ_TYPE_MSI 129 
#define  IRQ_TYPE_MSIX 128 
 int /*<<< orphan*/  PCI_IRQ_LEGACY ; 
 int /*<<< orphan*/  PCI_IRQ_MSI ; 
 int /*<<< orphan*/  PCI_IRQ_MSIX ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 int pci_alloc_irq_vectors (struct pci_dev*,int,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool pci_endpoint_test_alloc_irq_vectors(struct pci_endpoint_test *test,
						int type)
{
	int irq = -1;
	struct pci_dev *pdev = test->pdev;
	struct device *dev = &pdev->dev;
	bool res = true;

	switch (type) {
	case IRQ_TYPE_LEGACY:
		irq = pci_alloc_irq_vectors(pdev, 1, 1, PCI_IRQ_LEGACY);
		if (irq < 0)
			dev_err(dev, "Failed to get Legacy interrupt\n");
		break;
	case IRQ_TYPE_MSI:
		irq = pci_alloc_irq_vectors(pdev, 1, 32, PCI_IRQ_MSI);
		if (irq < 0)
			dev_err(dev, "Failed to get MSI interrupts\n");
		break;
	case IRQ_TYPE_MSIX:
		irq = pci_alloc_irq_vectors(pdev, 1, 2048, PCI_IRQ_MSIX);
		if (irq < 0)
			dev_err(dev, "Failed to get MSI-X interrupts\n");
		break;
	default:
		dev_err(dev, "Invalid IRQ type selected\n");
	}

	if (irq < 0) {
		irq = 0;
		res = false;
	}
	test->num_irqs = irq;

	return res;
}