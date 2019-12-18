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
 int /*<<< orphan*/  DRV_MODULE_NAME ; 
 int /*<<< orphan*/  IRQF_SHARED ; 
#define  IRQ_TYPE_LEGACY 130 
#define  IRQ_TYPE_MSI 129 
#define  IRQ_TYPE_MSIX 128 
 int /*<<< orphan*/  dev_err (struct device*,char*,int /*<<< orphan*/ ,...) ; 
 int devm_request_irq (struct device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct pci_endpoint_test*) ; 
 int irq_type ; 
 int /*<<< orphan*/  pci_endpoint_test_irqhandler ; 
 int /*<<< orphan*/  pci_irq_vector (struct pci_dev*,int) ; 

__attribute__((used)) static bool pci_endpoint_test_request_irq(struct pci_endpoint_test *test)
{
	int i;
	int err;
	struct pci_dev *pdev = test->pdev;
	struct device *dev = &pdev->dev;

	for (i = 0; i < test->num_irqs; i++) {
		err = devm_request_irq(dev, pci_irq_vector(pdev, i),
				       pci_endpoint_test_irqhandler,
				       IRQF_SHARED, DRV_MODULE_NAME, test);
		if (err)
			goto fail;
	}

	return true;

fail:
	switch (irq_type) {
	case IRQ_TYPE_LEGACY:
		dev_err(dev, "Failed to request IRQ %d for Legacy\n",
			pci_irq_vector(pdev, i));
		break;
	case IRQ_TYPE_MSI:
		dev_err(dev, "Failed to request IRQ %d for MSI %d\n",
			pci_irq_vector(pdev, i),
			i + 1);
		break;
	case IRQ_TYPE_MSIX:
		dev_err(dev, "Failed to request IRQ %d for MSI-X %d\n",
			pci_irq_vector(pdev, i),
			i + 1);
		break;
	}

	return false;
}