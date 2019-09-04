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
typedef  int uint32_t ;
struct pci_bus {int /*<<< orphan*/  number; } ;

/* Variables and functions */
 int PCIBIOS_DEVICE_NOT_FOUND ; 
 int PCIBIOS_FUNC_NOT_SUPPORTED ; 
 int PCIBIOS_SUCCESSFUL ; 
 int /*<<< orphan*/  PCICONFDREG ; 
 int readl (int /*<<< orphan*/ ) ; 
 scalar_t__ set_pci_configuration_address (int /*<<< orphan*/ ,unsigned int,int) ; 

__attribute__((used)) static int pci_config_read(struct pci_bus *bus, unsigned int devfn, int where,
			   int size, uint32_t *val)
{
	uint32_t data;

	*val = 0xffffffffU;
	if (set_pci_configuration_address(bus->number, devfn, where) < 0)
		return PCIBIOS_DEVICE_NOT_FOUND;

	data = readl(PCICONFDREG);

	switch (size) {
	case 1:
		*val = (data >> ((where & 3) << 3)) & 0xffU;
		break;
	case 2:
		*val = (data >> ((where & 2) << 3)) & 0xffffU;
		break;
	case 4:
		*val = data;
		break;
	default:
		return PCIBIOS_FUNC_NOT_SUPPORTED;
	}

	return PCIBIOS_SUCCESSFUL;
}