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
struct pci_dev {int dummy; } ;
struct nicvf {int num_vec; int* irq_allocated; struct nicvf** napi; int /*<<< orphan*/ * affinity_mask; struct pci_dev* pdev; } ;

/* Variables and functions */
 int NICVF_INTR_ID_SQ ; 
 int /*<<< orphan*/  free_cpumask_var (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct nicvf*) ; 
 int /*<<< orphan*/  irq_set_affinity_hint (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pci_free_irq_vectors (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_irq_vector (struct pci_dev*,int) ; 

__attribute__((used)) static void nicvf_unregister_interrupts(struct nicvf *nic)
{
	struct pci_dev *pdev = nic->pdev;
	int irq;

	/* Free registered interrupts */
	for (irq = 0; irq < nic->num_vec; irq++) {
		if (!nic->irq_allocated[irq])
			continue;

		irq_set_affinity_hint(pci_irq_vector(pdev, irq), NULL);
		free_cpumask_var(nic->affinity_mask[irq]);

		if (irq < NICVF_INTR_ID_SQ)
			free_irq(pci_irq_vector(pdev, irq), nic->napi[irq]);
		else
			free_irq(pci_irq_vector(pdev, irq), nic);

		nic->irq_allocated[irq] = false;
	}

	/* Disable MSI-X */
	pci_free_irq_vectors(pdev);
	nic->num_vec = 0;
}