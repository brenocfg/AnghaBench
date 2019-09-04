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
struct genwqe_dev {int /*<<< orphan*/  pci_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  PCI_IRQ_MSI ; 
 int pci_alloc_irq_vectors (int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ; 

int genwqe_set_interrupt_capability(struct genwqe_dev *cd, int count)
{
	int rc;

	rc = pci_alloc_irq_vectors(cd->pci_dev, 1, count, PCI_IRQ_MSI);
	if (rc < 0)
		return rc;
	return 0;
}