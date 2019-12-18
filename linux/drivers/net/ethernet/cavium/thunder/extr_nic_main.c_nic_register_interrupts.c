#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct nicpf {int num_vec; int* irq_allocated; TYPE_1__* pdev; int /*<<< orphan*/ * irq_name; } ;
struct TYPE_5__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int NIC_PF_INTR_ID_MBOX0 ; 
 int /*<<< orphan*/  PCI_IRQ_MSIX ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  nic_enable_mbx_intr (struct nicpf*) ; 
 int /*<<< orphan*/  nic_free_all_interrupts (struct nicpf*) ; 
 int /*<<< orphan*/  nic_mbx_intr_handler ; 
 int pci_alloc_irq_vectors (TYPE_1__*,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_free_irq_vectors (TYPE_1__*) ; 
 int /*<<< orphan*/  pci_irq_vector (TYPE_1__*,int) ; 
 int pci_msix_vec_count (TYPE_1__*) ; 
 int request_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct nicpf*) ; 
 int /*<<< orphan*/  sprintf (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static int nic_register_interrupts(struct nicpf *nic)
{
	int i, ret;
	nic->num_vec = pci_msix_vec_count(nic->pdev);

	/* Enable MSI-X */
	ret = pci_alloc_irq_vectors(nic->pdev, nic->num_vec, nic->num_vec,
				    PCI_IRQ_MSIX);
	if (ret < 0) {
		dev_err(&nic->pdev->dev,
			"Request for #%d msix vectors failed, returned %d\n",
			   nic->num_vec, ret);
		return 1;
	}

	/* Register mailbox interrupt handler */
	for (i = NIC_PF_INTR_ID_MBOX0; i < nic->num_vec; i++) {
		sprintf(nic->irq_name[i],
			"NICPF Mbox%d", (i - NIC_PF_INTR_ID_MBOX0));

		ret = request_irq(pci_irq_vector(nic->pdev, i),
				  nic_mbx_intr_handler, 0,
				  nic->irq_name[i], nic);
		if (ret)
			goto fail;

		nic->irq_allocated[i] = true;
	}

	/* Enable mailbox interrupt */
	nic_enable_mbx_intr(nic);
	return 0;

fail:
	dev_err(&nic->pdev->dev, "Request irq failed\n");
	nic_free_all_interrupts(nic);
	pci_free_irq_vectors(nic->pdev);
	nic->num_vec = 0;
	return ret;
}