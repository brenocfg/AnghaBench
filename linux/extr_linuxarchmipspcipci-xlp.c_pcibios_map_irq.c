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
typedef  int /*<<< orphan*/  u8 ;
struct pci_dev {int /*<<< orphan*/  devfn; } ;

/* Variables and functions */
 int PCI_FUNC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PIC_PCIE_LINK_LEGACY_IRQ (int) ; 
 int nlm_irq_to_xirq (int,int /*<<< orphan*/ ) ; 
 struct pci_dev* xlp_get_pcie_link (struct pci_dev const*) ; 
 int xlp_socdev_to_node (struct pci_dev*) ; 

int pcibios_map_irq(const struct pci_dev *dev, u8 slot, u8 pin)
{
	struct pci_dev *lnkdev;
	int lnkfunc, node;

	/*
	 * For XLP PCIe, there is an IRQ per Link, find out which
	 * link the device is on to assign interrupts
	*/
	lnkdev = xlp_get_pcie_link(dev);
	if (lnkdev == NULL)
		return 0;

	lnkfunc = PCI_FUNC(lnkdev->devfn);
	node = xlp_socdev_to_node(lnkdev);

	return nlm_irq_to_xirq(node, PIC_PCIE_LINK_LEGACY_IRQ(lnkfunc));
}