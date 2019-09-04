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
typedef  scalar_t__ u_char ;
struct pci_controller {scalar_t__ first_busno; } ;

/* Variables and functions */
 int PCIBIOS_DEVICE_NOT_FOUND ; 
 int PCIBIOS_SUCCESSFUL ; 
 int PCI_FUNC (scalar_t__) ; 
 int PCI_SLOT (scalar_t__) ; 

int uli_exclude_device(struct pci_controller *hose,
			u_char bus, u_char devfn)
{
	if (bus == (hose->first_busno + 2)) {
		/* exclude Modem controller */
		if ((PCI_SLOT(devfn) == 29) && (PCI_FUNC(devfn) == 1))
			return PCIBIOS_DEVICE_NOT_FOUND;

		/* exclude HD Audio controller */
		if ((PCI_SLOT(devfn) == 29) && (PCI_FUNC(devfn) == 2))
			return PCIBIOS_DEVICE_NOT_FOUND;
	}

	return PCIBIOS_SUCCESSFUL;
}