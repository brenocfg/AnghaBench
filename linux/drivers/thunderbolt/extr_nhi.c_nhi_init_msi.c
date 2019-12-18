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
struct tb_nhi {struct pci_dev* pdev; int /*<<< orphan*/  interrupt_work; int /*<<< orphan*/  msix_ida; } ;
struct pci_dev {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IRQF_NO_SUSPEND ; 
 int MSIX_MAX_VECS ; 
 int MSIX_MIN_VECS ; 
 int /*<<< orphan*/  PCI_IRQ_MSI ; 
 int /*<<< orphan*/  PCI_IRQ_MSIX ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int devm_request_irq (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,struct tb_nhi*) ; 
 int /*<<< orphan*/  ida_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nhi_disable_interrupts (struct tb_nhi*) ; 
 int /*<<< orphan*/  nhi_enable_int_throttling (struct tb_nhi*) ; 
 int /*<<< orphan*/  nhi_interrupt_work ; 
 int /*<<< orphan*/  nhi_msi ; 
 int pci_alloc_irq_vectors (struct pci_dev*,int,int,int /*<<< orphan*/ ) ; 
 int pci_irq_vector (struct pci_dev*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int nhi_init_msi(struct tb_nhi *nhi)
{
	struct pci_dev *pdev = nhi->pdev;
	int res, irq, nvec;

	/* In case someone left them on. */
	nhi_disable_interrupts(nhi);

	nhi_enable_int_throttling(nhi);

	ida_init(&nhi->msix_ida);

	/*
	 * The NHI has 16 MSI-X vectors or a single MSI. We first try to
	 * get all MSI-X vectors and if we succeed, each ring will have
	 * one MSI-X. If for some reason that does not work out, we
	 * fallback to a single MSI.
	 */
	nvec = pci_alloc_irq_vectors(pdev, MSIX_MIN_VECS, MSIX_MAX_VECS,
				     PCI_IRQ_MSIX);
	if (nvec < 0) {
		nvec = pci_alloc_irq_vectors(pdev, 1, 1, PCI_IRQ_MSI);
		if (nvec < 0)
			return nvec;

		INIT_WORK(&nhi->interrupt_work, nhi_interrupt_work);

		irq = pci_irq_vector(nhi->pdev, 0);
		if (irq < 0)
			return irq;

		res = devm_request_irq(&pdev->dev, irq, nhi_msi,
				       IRQF_NO_SUSPEND, "thunderbolt", nhi);
		if (res) {
			dev_err(&pdev->dev, "request_irq failed, aborting\n");
			return res;
		}
	}

	return 0;
}