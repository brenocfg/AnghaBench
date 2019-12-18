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
 int EAGAIN ; 
 int /*<<< orphan*/  might_sleep () ; 
 int pci_bridge_secondary_bus_reset (int /*<<< orphan*/ ) ; 
 int pci_bus_reset (struct pci_bus*,int) ; 
 int /*<<< orphan*/  pci_bus_restore_locked (struct pci_bus*) ; 
 int /*<<< orphan*/  pci_bus_save_and_disable_locked (struct pci_bus*) ; 
 scalar_t__ pci_bus_trylock (struct pci_bus*) ; 
 int /*<<< orphan*/  pci_bus_unlock (struct pci_bus*) ; 

__attribute__((used)) static int __pci_reset_bus(struct pci_bus *bus)
{
	int rc;

	rc = pci_bus_reset(bus, 1);
	if (rc)
		return rc;

	if (pci_bus_trylock(bus)) {
		pci_bus_save_and_disable_locked(bus);
		might_sleep();
		rc = pci_bridge_secondary_bus_reset(bus->self);
		pci_bus_restore_locked(bus);
		pci_bus_unlock(bus);
	} else
		rc = -EAGAIN;

	return rc;
}