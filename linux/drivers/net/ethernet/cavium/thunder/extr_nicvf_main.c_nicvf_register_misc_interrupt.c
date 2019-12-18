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
struct nicvf {int* irq_allocated; int /*<<< orphan*/ * irq_name; TYPE_1__* pdev; int /*<<< orphan*/  num_vec; int /*<<< orphan*/  netdev; } ;
struct TYPE_4__ {scalar_t__ msix_enabled; } ;

/* Variables and functions */
 int NICVF_INTR_ID_MISC ; 
 int /*<<< orphan*/  NICVF_INTR_MBOX ; 
 int /*<<< orphan*/  PCI_IRQ_MSIX ; 
 int /*<<< orphan*/  netdev_err (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nicvf_check_pf_ready (struct nicvf*) ; 
 int /*<<< orphan*/  nicvf_disable_intr (struct nicvf*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nicvf_enable_intr (struct nicvf*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nicvf_misc_intr_handler ; 
 int /*<<< orphan*/  nicvf_unregister_interrupts (struct nicvf*) ; 
 int pci_alloc_irq_vectors (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_irq_vector (TYPE_1__*,int) ; 
 int /*<<< orphan*/  pci_msix_vec_count (TYPE_1__*) ; 
 int request_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct nicvf*) ; 
 int /*<<< orphan*/  sprintf (int /*<<< orphan*/ ,char*,char*) ; 

__attribute__((used)) static int nicvf_register_misc_interrupt(struct nicvf *nic)
{
	int ret = 0;
	int irq = NICVF_INTR_ID_MISC;

	/* Return if mailbox interrupt is already registered */
	if (nic->pdev->msix_enabled)
		return 0;

	/* Enable MSI-X */
	nic->num_vec = pci_msix_vec_count(nic->pdev);
	ret = pci_alloc_irq_vectors(nic->pdev, nic->num_vec, nic->num_vec,
				    PCI_IRQ_MSIX);
	if (ret < 0) {
		netdev_err(nic->netdev,
			   "Req for #%d msix vectors failed\n", nic->num_vec);
		return 1;
	}

	sprintf(nic->irq_name[irq], "%s Mbox", "NICVF");
	/* Register Misc interrupt */
	ret = request_irq(pci_irq_vector(nic->pdev, irq),
			  nicvf_misc_intr_handler, 0, nic->irq_name[irq], nic);

	if (ret)
		return ret;
	nic->irq_allocated[irq] = true;

	/* Enable mailbox interrupt */
	nicvf_enable_intr(nic, NICVF_INTR_MBOX, 0);

	/* Check if VF is able to communicate with PF */
	if (!nicvf_check_pf_ready(nic)) {
		nicvf_disable_intr(nic, NICVF_INTR_MBOX, 0);
		nicvf_unregister_interrupts(nic);
		return 1;
	}

	return 0;
}