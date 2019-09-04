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
struct pci_bus {int dummy; } ;
struct ar2315_pci_ctrl {int dummy; } ;

/* Variables and functions */
 scalar_t__ AR2315_PCI_HOST_SLOT ; 
 int PCIBIOS_DEVICE_NOT_FOUND ; 
 scalar_t__ PCI_SLOT (unsigned int) ; 
 struct ar2315_pci_ctrl* ar2315_pci_bus_to_apc (struct pci_bus*) ; 
 int ar2315_pci_cfg_access (struct ar2315_pci_ctrl*,unsigned int,int,int,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int ar2315_pci_cfg_write(struct pci_bus *bus, unsigned devfn, int where,
				int size, u32 value)
{
	struct ar2315_pci_ctrl *apc = ar2315_pci_bus_to_apc(bus);

	if (PCI_SLOT(devfn) == AR2315_PCI_HOST_SLOT)
		return PCIBIOS_DEVICE_NOT_FOUND;

	return ar2315_pci_cfg_access(apc, devfn, where, size, &value, true);
}