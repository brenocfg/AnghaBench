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
typedef  int u16 ;
struct resource {int flags; int start; } ;
struct pci_dev {int /*<<< orphan*/  bus; } ;
struct pci_controller {scalar_t__* mem_offset; scalar_t__ io_base_virt; TYPE_1__* mem_resources; } ;
struct pci_bus_region {scalar_t__ start; } ;
struct pci_bus {struct pci_dev* self; } ;
typedef  int resource_size_t ;
struct TYPE_2__ {int flags; scalar_t__ start; } ;

/* Variables and functions */
 int IORESOURCE_MEM ; 
 int /*<<< orphan*/  PCI_COMMAND ; 
 int PCI_COMMAND_IO ; 
 int PCI_COMMAND_MEMORY ; 
 int /*<<< orphan*/  PCI_PROBE_ONLY ; 
 int _IO_BASE ; 
 struct pci_controller* pci_bus_to_host (struct pci_bus*) ; 
 scalar_t__ pci_has_flag (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_read_config_word (struct pci_dev*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  pcibios_resource_to_bus (int /*<<< orphan*/ ,struct pci_bus_region*,struct resource*) ; 

__attribute__((used)) static int pcibios_uninitialized_bridge_resource(struct pci_bus *bus,
						 struct resource *res)
{
	struct pci_controller *hose = pci_bus_to_host(bus);
	struct pci_dev *dev = bus->self;
	resource_size_t offset;
	struct pci_bus_region region;
	u16 command;
	int i;

	/* We don't do anything if PCI_PROBE_ONLY is set */
	if (pci_has_flag(PCI_PROBE_ONLY))
		return 0;

	/* Job is a bit different between memory and IO */
	if (res->flags & IORESOURCE_MEM) {
		pcibios_resource_to_bus(dev->bus, &region, res);

		/* If the BAR is non-0 then it's probably been initialized */
		if (region.start != 0)
			return 0;

		/* The BAR is 0, let's check if memory decoding is enabled on
		 * the bridge. If not, we consider it unassigned
		 */
		pci_read_config_word(dev, PCI_COMMAND, &command);
		if ((command & PCI_COMMAND_MEMORY) == 0)
			return 1;

		/* Memory decoding is enabled and the BAR is 0. If any of the bridge
		 * resources covers that starting address (0 then it's good enough for
		 * us for memory space)
		 */
		for (i = 0; i < 3; i++) {
			if ((hose->mem_resources[i].flags & IORESOURCE_MEM) &&
			    hose->mem_resources[i].start == hose->mem_offset[i])
				return 0;
		}

		/* Well, it starts at 0 and we know it will collide so we may as
		 * well consider it as unassigned. That covers the Apple case.
		 */
		return 1;
	} else {
		/* If the BAR is non-0, then we consider it assigned */
		offset = (unsigned long)hose->io_base_virt - _IO_BASE;
		if (((res->start - offset) & 0xfffffffful) != 0)
			return 0;

		/* Here, we are a bit different than memory as typically IO space
		 * starting at low addresses -is- valid. What we do instead if that
		 * we consider as unassigned anything that doesn't have IO enabled
		 * in the PCI command register, and that's it.
		 */
		pci_read_config_word(dev, PCI_COMMAND, &command);
		if (command & PCI_COMMAND_IO)
			return 0;

		/* It's starting at 0 and IO is disabled in the bridge, consider
		 * it unassigned
		 */
		return 1;
	}
}