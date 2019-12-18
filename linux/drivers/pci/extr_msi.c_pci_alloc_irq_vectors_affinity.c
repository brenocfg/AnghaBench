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
struct pci_dev {scalar_t__ irq; } ;
struct irq_affinity {int /*<<< orphan*/  member_0; } ;

/* Variables and functions */
 int ENOSPC ; 
 unsigned int PCI_IRQ_AFFINITY ; 
 unsigned int PCI_IRQ_LEGACY ; 
 unsigned int PCI_IRQ_MSI ; 
 unsigned int PCI_IRQ_MSIX ; 
 scalar_t__ WARN_ON (struct irq_affinity*) ; 
 int __pci_enable_msi_range (struct pci_dev*,unsigned int,unsigned int,struct irq_affinity*) ; 
 int __pci_enable_msix_range (struct pci_dev*,int /*<<< orphan*/ *,unsigned int,unsigned int,struct irq_affinity*,unsigned int) ; 
 int /*<<< orphan*/  irq_create_affinity_masks (int,struct irq_affinity*) ; 
 int /*<<< orphan*/  pci_intx (struct pci_dev*,int) ; 

int pci_alloc_irq_vectors_affinity(struct pci_dev *dev, unsigned int min_vecs,
				   unsigned int max_vecs, unsigned int flags,
				   struct irq_affinity *affd)
{
	struct irq_affinity msi_default_affd = {0};
	int msix_vecs = -ENOSPC;
	int msi_vecs = -ENOSPC;

	if (flags & PCI_IRQ_AFFINITY) {
		if (!affd)
			affd = &msi_default_affd;
	} else {
		if (WARN_ON(affd))
			affd = NULL;
	}

	if (flags & PCI_IRQ_MSIX) {
		msix_vecs = __pci_enable_msix_range(dev, NULL, min_vecs,
						    max_vecs, affd, flags);
		if (msix_vecs > 0)
			return msix_vecs;
	}

	if (flags & PCI_IRQ_MSI) {
		msi_vecs = __pci_enable_msi_range(dev, min_vecs, max_vecs,
						  affd);
		if (msi_vecs > 0)
			return msi_vecs;
	}

	/* use legacy IRQ if allowed */
	if (flags & PCI_IRQ_LEGACY) {
		if (min_vecs == 1 && dev->irq) {
			/*
			 * Invoke the affinity spreading logic to ensure that
			 * the device driver can adjust queue configuration
			 * for the single interrupt case.
			 */
			if (affd)
				irq_create_affinity_masks(1, affd);
			pci_intx(dev, 1);
			return 1;
		}
	}

	if (msix_vecs == -ENOSPC)
		return -ENOSPC;
	return msi_vecs;
}