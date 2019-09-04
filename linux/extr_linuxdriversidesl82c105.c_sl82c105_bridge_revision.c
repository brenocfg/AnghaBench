#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct pci_dev {scalar_t__ vendor; scalar_t__ device; int class; int revision; int /*<<< orphan*/  devfn; TYPE_1__* bus; } ;
struct TYPE_2__ {int /*<<< orphan*/  number; } ;

/* Variables and functions */
 int PCI_CLASS_BRIDGE_ISA ; 
 int /*<<< orphan*/  PCI_DEVFN (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ PCI_DEVICE_ID_WINBOND_83C553 ; 
 int /*<<< orphan*/  PCI_SLOT (int /*<<< orphan*/ ) ; 
 scalar_t__ PCI_VENDOR_ID_WINBOND ; 
 int /*<<< orphan*/  pci_dev_put (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_domain_nr (TYPE_1__*) ; 
 struct pci_dev* pci_get_domain_bus_and_slot (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static u8 sl82c105_bridge_revision(struct pci_dev *dev)
{
	struct pci_dev *bridge;

	/*
	 * The bridge should be part of the same device, but function 0.
	 */
	bridge = pci_get_domain_bus_and_slot(pci_domain_nr(dev->bus),
					dev->bus->number,
					PCI_DEVFN(PCI_SLOT(dev->devfn), 0));
	if (!bridge)
		return -1;

	/*
	 * Make sure it is a Winbond 553 and is an ISA bridge.
	 */
	if (bridge->vendor != PCI_VENDOR_ID_WINBOND ||
	    bridge->device != PCI_DEVICE_ID_WINBOND_83C553 ||
	    bridge->class >> 8 != PCI_CLASS_BRIDGE_ISA) {
	    	pci_dev_put(bridge);
		return -1;
	}
	/*
	 * We need to find function 0's revision, not function 1
	 */
	pci_dev_put(bridge);

	return bridge->revision;
}