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
typedef  int /*<<< orphan*/  u16 ;
struct resource {int flags; scalar_t__ start; scalar_t__ end; } ;
struct pci_dev {scalar_t__ hdr_type; int class; struct resource* resource; scalar_t__ is_virtfn; } ;
typedef  int /*<<< orphan*/  resource_size_t ;

/* Variables and functions */
 int IORESOURCE_MEM ; 
 int IORESOURCE_UNSET ; 
 int PCI_BRIDGE_RESOURCES ; 
 int PCI_CLASS_BRIDGE_HOST ; 
 int /*<<< orphan*/  PCI_COMMAND ; 
 int /*<<< orphan*/  PCI_COMMAND_MEMORY ; 
 scalar_t__ PCI_HEADER_TYPE_BRIDGE ; 
 scalar_t__ PCI_HEADER_TYPE_NORMAL ; 
 int PCI_NUM_RESOURCES ; 
 int PCI_ROM_RESOURCE ; 
 int /*<<< orphan*/  pci_disable_bridge_window (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_read_config_word (struct pci_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pci_request_resource_alignment (struct pci_dev*,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pci_specified_resource_alignment (struct pci_dev*,int*) ; 
 int /*<<< orphan*/  pci_warn (struct pci_dev*,char*) ; 
 int /*<<< orphan*/  pci_write_config_word (struct pci_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ resource_size (struct resource*) ; 

void pci_reassigndev_resource_alignment(struct pci_dev *dev)
{
	int i;
	struct resource *r;
	resource_size_t align;
	u16 command;
	bool resize = false;

	/*
	 * VF BARs are read-only zero according to SR-IOV spec r1.1, sec
	 * 3.4.1.11.  Their resources are allocated from the space
	 * described by the VF BARx register in the PF's SR-IOV capability.
	 * We can't influence their alignment here.
	 */
	if (dev->is_virtfn)
		return;

	/* check if specified PCI is target device to reassign */
	align = pci_specified_resource_alignment(dev, &resize);
	if (!align)
		return;

	if (dev->hdr_type == PCI_HEADER_TYPE_NORMAL &&
	    (dev->class >> 8) == PCI_CLASS_BRIDGE_HOST) {
		pci_warn(dev, "Can't reassign resources to host bridge\n");
		return;
	}

	pci_read_config_word(dev, PCI_COMMAND, &command);
	command &= ~PCI_COMMAND_MEMORY;
	pci_write_config_word(dev, PCI_COMMAND, command);

	for (i = 0; i <= PCI_ROM_RESOURCE; i++)
		pci_request_resource_alignment(dev, i, align, resize);

	/*
	 * Need to disable bridge's resource window,
	 * to enable the kernel to reassign new resource
	 * window later on.
	 */
	if (dev->hdr_type == PCI_HEADER_TYPE_BRIDGE) {
		for (i = PCI_BRIDGE_RESOURCES; i < PCI_NUM_RESOURCES; i++) {
			r = &dev->resource[i];
			if (!(r->flags & IORESOURCE_MEM))
				continue;
			r->flags |= IORESOURCE_UNSET;
			r->end = resource_size(r) - 1;
			r->start = 0;
		}
		pci_disable_bridge_window(dev);
	}
}