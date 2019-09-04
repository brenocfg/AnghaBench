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
typedef  int u32 ;
typedef  int u16 ;
struct pci_bus {int dummy; } ;

/* Variables and functions */
 int PCIBIOS_BAD_REGISTER_NUMBER ; 
 int PCIBIOS_SUCCESSFUL ; 
 int /*<<< orphan*/  PCI_ACCESS_READ ; 
 int /*<<< orphan*/  PCI_ACCESS_WRITE ; 
 scalar_t__ msp_pcibios_config_access (int /*<<< orphan*/ ,struct pci_bus*,unsigned int,int,int*) ; 

__attribute__((used)) static int
msp_pcibios_write_config_word(struct pci_bus *bus,
				unsigned int devfn,
				int where,
				u16 val)
{
	u32 data = 0;

	/* Fixed non-compliance: if (where & 1) */
	if ((where & 3) == 3)
		return PCIBIOS_BAD_REGISTER_NUMBER;

	/* read config space */
	if (msp_pcibios_config_access(PCI_ACCESS_READ, bus, devfn,
					where, &data))
		return -1;

	/* modify the word within the dword */
	data = (data & ~(0xffff << ((where & 3) << 3))) |
			(val << ((where & 3) << 3));

	/* write back the full dword */
	if (msp_pcibios_config_access(PCI_ACCESS_WRITE, bus, devfn,
					where, &data))
		return -1;

	return PCIBIOS_SUCCESSFUL;
}