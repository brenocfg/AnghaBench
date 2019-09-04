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
struct cvm_mmc_host {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  PCI_IRQ_MSIX ; 
 int /*<<< orphan*/  cvm_mmc_interrupt ; 
 int /*<<< orphan*/ * cvm_mmc_irq_names ; 
 int devm_request_irq (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct cvm_mmc_host*) ; 
 int pci_alloc_irq_vectors (struct pci_dev*,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_irq_vector (struct pci_dev*,int) ; 

__attribute__((used)) static int thunder_mmc_register_interrupts(struct cvm_mmc_host *host,
					   struct pci_dev *pdev)
{
	int nvec, ret, i;

	nvec = pci_alloc_irq_vectors(pdev, 1, 9, PCI_IRQ_MSIX);
	if (nvec < 0)
		return nvec;

	/* register interrupts */
	for (i = 0; i < nvec; i++) {
		ret = devm_request_irq(&pdev->dev, pci_irq_vector(pdev, i),
				       cvm_mmc_interrupt,
				       0, cvm_mmc_irq_names[i], host);
		if (ret)
			return ret;
	}
	return 0;
}