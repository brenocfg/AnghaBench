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
struct pci_dev {scalar_t__ msix_enabled; } ;
struct aq_nic_s {unsigned int msix_entry_mask; int /*<<< orphan*/ * aq_vec; struct pci_dev* pdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  irq_set_affinity_hint (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pci_irq_vector (struct pci_dev*,unsigned int) ; 

void aq_pci_func_free_irqs(struct aq_nic_s *self)
{
	struct pci_dev *pdev = self->pdev;
	unsigned int i = 0U;

	for (i = 32U; i--;) {
		if (!((1U << i) & self->msix_entry_mask))
			continue;

		if (pdev->msix_enabled)
			irq_set_affinity_hint(pci_irq_vector(pdev, i), NULL);
		free_irq(pci_irq_vector(pdev, i), self->aq_vec[i]);
		self->msix_entry_mask &= ~(1U << i);
	}
}