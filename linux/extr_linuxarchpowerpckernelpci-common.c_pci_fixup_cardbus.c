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
 int /*<<< orphan*/  pcibios_setup_bus_devices (struct pci_bus*) ; 

void pci_fixup_cardbus(struct pci_bus *bus)
{
	/* Now fixup devices on that bus */
	pcibios_setup_bus_devices(bus);
}