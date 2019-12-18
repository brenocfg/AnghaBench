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
struct pci_bus {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  pci_assign_unassigned_bus_resources (struct pci_bus*) ; 
 int /*<<< orphan*/  pci_bus_add_devices (struct pci_bus*) ; 
 unsigned int pci_scan_child_bus (struct pci_bus*) ; 

unsigned int pci_rescan_bus(struct pci_bus *bus)
{
	unsigned int max;

	max = pci_scan_child_bus(bus);
	pci_assign_unassigned_bus_resources(bus);
	pci_bus_add_devices(bus);

	return max;
}