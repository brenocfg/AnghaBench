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
struct pci_bus {int /*<<< orphan*/  dev; TYPE_1__* ops; int /*<<< orphan*/  node; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* remove_bus ) (struct pci_bus*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  device_unregister (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  down_write (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pci_bus_release_busn_res (struct pci_bus*) ; 
 int /*<<< orphan*/  pci_bus_sem ; 
 int /*<<< orphan*/  pci_proc_detach_bus (struct pci_bus*) ; 
 int /*<<< orphan*/  pci_remove_legacy_files (struct pci_bus*) ; 
 int /*<<< orphan*/  pcibios_remove_bus (struct pci_bus*) ; 
 int /*<<< orphan*/  stub1 (struct pci_bus*) ; 
 int /*<<< orphan*/  up_write (int /*<<< orphan*/ *) ; 

void pci_remove_bus(struct pci_bus *bus)
{
	pci_proc_detach_bus(bus);

	down_write(&pci_bus_sem);
	list_del(&bus->node);
	pci_bus_release_busn_res(bus);
	up_write(&pci_bus_sem);
	pci_remove_legacy_files(bus);

	if (bus->ops->remove_bus)
		bus->ops->remove_bus(bus);

	pcibios_remove_bus(bus);
	device_unregister(&bus->dev);
}