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
typedef  int /*<<< orphan*/  u32 ;

/* Variables and functions */
 scalar_t__ PCI_FUNC (int /*<<< orphan*/ ) ; 
 int PCI_SLOT (int /*<<< orphan*/ ) ; 
 scalar_t__ orion5x_pci_cardbus_mode ; 
 int orion5x_pci_local_bus_nr () ; 

__attribute__((used)) static int orion5x_pci_valid_config(int bus, u32 devfn)
{
	if (bus == orion5x_pci_local_bus_nr()) {
		/*
		 * Don't go out for local device
		 */
		if (PCI_SLOT(devfn) == 0 && PCI_FUNC(devfn) != 0)
			return 0;

		/*
		 * When the PCI signals are directly connected to a
		 * Cardbus slot, ignore all but device IDs 0 and 1.
		 */
		if (orion5x_pci_cardbus_mode && PCI_SLOT(devfn) > 1)
			return 0;
	}

	return 1;
}