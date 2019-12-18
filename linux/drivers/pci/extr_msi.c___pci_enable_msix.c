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
struct pci_dev {scalar_t__ msi_enabled; } ;
struct msix_entry {int entry; } ;
struct irq_affinity {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int PCI_IRQ_VIRTUAL ; 
 int msix_capability_init (struct pci_dev*,struct msix_entry*,int,struct irq_affinity*) ; 
 int /*<<< orphan*/  pci_info (struct pci_dev*,char*) ; 
 int /*<<< orphan*/  pci_msi_supported (struct pci_dev*,int) ; 
 int pci_msix_vec_count (struct pci_dev*) ; 

__attribute__((used)) static int __pci_enable_msix(struct pci_dev *dev, struct msix_entry *entries,
			     int nvec, struct irq_affinity *affd, int flags)
{
	int nr_entries;
	int i, j;

	if (!pci_msi_supported(dev, nvec))
		return -EINVAL;

	nr_entries = pci_msix_vec_count(dev);
	if (nr_entries < 0)
		return nr_entries;
	if (nvec > nr_entries && !(flags & PCI_IRQ_VIRTUAL))
		return nr_entries;

	if (entries) {
		/* Check for any invalid entries */
		for (i = 0; i < nvec; i++) {
			if (entries[i].entry >= nr_entries)
				return -EINVAL;		/* invalid entry */
			for (j = i + 1; j < nvec; j++) {
				if (entries[i].entry == entries[j].entry)
					return -EINVAL;	/* duplicate entry */
			}
		}
	}

	/* Check whether driver already requested for MSI IRQ */
	if (dev->msi_enabled) {
		pci_info(dev, "can't enable MSI-X (MSI IRQ already assigned)\n");
		return -EINVAL;
	}
	return msix_capability_init(dev, entries, nvec, affd);
}