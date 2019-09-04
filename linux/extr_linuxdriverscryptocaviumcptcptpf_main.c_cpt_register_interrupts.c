#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct device {int dummy; } ;
struct cpt_device {TYPE_1__* pdev; } ;
struct TYPE_4__ {struct device dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  CPT_PF_INT_VEC_E_MBOXX (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CPT_PF_MSIX_VECTORS ; 
 int /*<<< orphan*/  PCI_IRQ_MSIX ; 
 int /*<<< orphan*/  cpt_enable_mbox_interrupts (struct cpt_device*) ; 
 int /*<<< orphan*/  cpt_mbx0_intr_handler ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,...) ; 
 int pci_alloc_irq_vectors (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_disable_msix (TYPE_1__*) ; 
 int /*<<< orphan*/  pci_irq_vector (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int request_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,struct cpt_device*) ; 

__attribute__((used)) static int cpt_register_interrupts(struct cpt_device *cpt)
{
	int ret;
	struct device *dev = &cpt->pdev->dev;

	/* Enable MSI-X */
	ret = pci_alloc_irq_vectors(cpt->pdev, CPT_PF_MSIX_VECTORS,
			CPT_PF_MSIX_VECTORS, PCI_IRQ_MSIX);
	if (ret < 0) {
		dev_err(&cpt->pdev->dev, "Request for #%d msix vectors failed\n",
			CPT_PF_MSIX_VECTORS);
		return ret;
	}

	/* Register mailbox interrupt handlers */
	ret = request_irq(pci_irq_vector(cpt->pdev, CPT_PF_INT_VEC_E_MBOXX(0)),
			  cpt_mbx0_intr_handler, 0, "CPT Mbox0", cpt);
	if (ret)
		goto fail;

	/* Enable mailbox interrupt */
	cpt_enable_mbox_interrupts(cpt);
	return 0;

fail:
	dev_err(dev, "Request irq failed\n");
	pci_disable_msix(cpt->pdev);
	return ret;
}