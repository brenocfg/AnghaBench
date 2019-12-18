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
struct pci_bus {int /*<<< orphan*/  self; } ;

/* Variables and functions */
 int ENOTTY ; 
 int /*<<< orphan*/  might_sleep () ; 
 int pci_bridge_secondary_bus_reset (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_bus_lock (struct pci_bus*) ; 
 int /*<<< orphan*/  pci_bus_resetable (struct pci_bus*) ; 
 int /*<<< orphan*/  pci_bus_unlock (struct pci_bus*) ; 

__attribute__((used)) static int pci_bus_reset(struct pci_bus *bus, int probe)
{
	int ret;

	if (!bus->self || !pci_bus_resetable(bus))
		return -ENOTTY;

	if (probe)
		return 0;

	pci_bus_lock(bus);

	might_sleep();

	ret = pci_bridge_secondary_bus_reset(bus->self);

	pci_bus_unlock(bus);

	return ret;
}