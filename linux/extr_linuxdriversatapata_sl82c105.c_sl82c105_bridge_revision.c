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
struct pci_dev {scalar_t__ vendor; scalar_t__ device; int class; int revision; int /*<<< orphan*/  devfn; int /*<<< orphan*/  bus; } ;

/* Variables and functions */
 int PCI_CLASS_BRIDGE_ISA ; 
 int /*<<< orphan*/  PCI_DEVFN (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ PCI_DEVICE_ID_WINBOND_83C553 ; 
 int /*<<< orphan*/  PCI_SLOT (int /*<<< orphan*/ ) ; 
 scalar_t__ PCI_VENDOR_ID_WINBOND ; 
 int /*<<< orphan*/  pci_dev_put (struct pci_dev*) ; 
 struct pci_dev* pci_get_slot (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int sl82c105_bridge_revision(struct pci_dev *pdev)
{
	struct pci_dev *bridge;

	/*
	 * The bridge should be part of the same device, but function 0.
	 */
	bridge = pci_get_slot(pdev->bus,
			       PCI_DEVFN(PCI_SLOT(pdev->devfn), 0));
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