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
struct pci_dev {int dev_flags; scalar_t__ is_virtfn; } ;

/* Variables and functions */
 int PCI_DEV_FLAGS_NO_RELAXED_ORDERING ; 
 int /*<<< orphan*/  PCI_EXP_DEVCTL ; 
 int /*<<< orphan*/  PCI_EXP_DEVCTL_RELAX_EN ; 
 struct pci_dev* pci_find_pcie_root_port (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_info (struct pci_dev*,char*) ; 
 int /*<<< orphan*/  pcie_capability_clear_word (struct pci_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pcie_relaxed_ordering_enabled (struct pci_dev*) ; 

__attribute__((used)) static void pci_configure_relaxed_ordering(struct pci_dev *dev)
{
	struct pci_dev *root;

	/* PCI_EXP_DEVICE_RELAX_EN is RsvdP in VFs */
	if (dev->is_virtfn)
		return;

	if (!pcie_relaxed_ordering_enabled(dev))
		return;

	/*
	 * For now, we only deal with Relaxed Ordering issues with Root
	 * Ports. Peer-to-Peer DMA is another can of worms.
	 */
	root = pci_find_pcie_root_port(dev);
	if (!root)
		return;

	if (root->dev_flags & PCI_DEV_FLAGS_NO_RELAXED_ORDERING) {
		pcie_capability_clear_word(dev, PCI_EXP_DEVCTL,
					   PCI_EXP_DEVCTL_RELAX_EN);
		pci_info(dev, "Relaxed Ordering disabled because the Root Port didn't support it\n");
	}
}