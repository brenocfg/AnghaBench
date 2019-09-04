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
struct pci_dev {int irq; int /*<<< orphan*/  devfn; int /*<<< orphan*/  bus; } ;
struct bridge_controller {int* pci_int; } ;

/* Variables and functions */
 struct bridge_controller* BRIDGE_CONTROLLER (int /*<<< orphan*/ ) ; 
 int PCI_SLOT (int /*<<< orphan*/ ) ; 
 struct pci_dev* bridge_root_dev (struct pci_dev*) ; 
 struct bridge_controller** irq_to_bridge ; 
 int* irq_to_slot ; 
 int request_bridge_irq (struct bridge_controller*) ; 

int pcibios_plat_dev_init(struct pci_dev *dev)
{
	struct bridge_controller *bc = BRIDGE_CONTROLLER(dev->bus);
	struct pci_dev *rdev = bridge_root_dev(dev);
	int slot = PCI_SLOT(rdev->devfn);
	int irq;

	irq = bc->pci_int[slot];
	if (irq == -1) {
		irq = request_bridge_irq(bc);
		if (irq < 0)
			return irq;

		bc->pci_int[slot] = irq;
	}

	irq_to_bridge[irq] = bc;
	irq_to_slot[irq] = slot;

	dev->irq = irq;

	return 0;
}