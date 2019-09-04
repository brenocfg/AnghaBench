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
struct TYPE_2__ {int /*<<< orphan*/  (* setup_bridge ) (struct pci_bus*,unsigned long) ;} ;
struct pci_controller {TYPE_1__ controller_ops; } ;
struct pci_bus {int dummy; } ;

/* Variables and functions */
 struct pci_controller* pci_bus_to_host (struct pci_bus*) ; 
 int /*<<< orphan*/  stub1 (struct pci_bus*,unsigned long) ; 

void pcibios_setup_bridge(struct pci_bus *bus, unsigned long type)
{
	struct pci_controller *hose = pci_bus_to_host(bus);

	if (hose->controller_ops.setup_bridge)
		hose->controller_ops.setup_bridge(bus, type);
}