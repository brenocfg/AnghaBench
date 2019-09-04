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
struct TYPE_2__ {int (* window_alignment ) (struct pci_bus*,unsigned long) ;} ;
struct pci_controller {TYPE_1__ controller_ops; } ;
struct pci_bus {int dummy; } ;
typedef  int resource_size_t ;

/* Variables and functions */
 struct pci_controller* pci_bus_to_host (struct pci_bus*) ; 
 int stub1 (struct pci_bus*,unsigned long) ; 

resource_size_t pcibios_window_alignment(struct pci_bus *bus,
					 unsigned long type)
{
	struct pci_controller *phb = pci_bus_to_host(bus);

	if (phb->controller_ops.window_alignment)
		return phb->controller_ops.window_alignment(bus, type);

	/*
	 * PCI core will figure out the default
	 * alignment: 4KiB for I/O and 1MiB for
	 * memory window.
	 */
	return 1;
}