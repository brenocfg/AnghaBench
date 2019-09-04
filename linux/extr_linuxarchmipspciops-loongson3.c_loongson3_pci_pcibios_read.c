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
struct pci_bus {int dummy; } ;

/* Variables and functions */
 int PCIBIOS_SUCCESSFUL ; 
 int /*<<< orphan*/  PCI_ACCESS_READ ; 
 int loongson3_pci_config_access (int /*<<< orphan*/ ,struct pci_bus*,unsigned int,int,int*) ; 

__attribute__((used)) static int loongson3_pci_pcibios_read(struct pci_bus *bus, unsigned int devfn,
				 int where, int size, u32 *val)
{
	u32 data = 0;
	int ret = loongson3_pci_config_access(PCI_ACCESS_READ,
			bus, devfn, where, &data);

	if (ret != PCIBIOS_SUCCESSFUL)
		return ret;

	if (size == 1)
		*val = (data >> ((where & 3) << 3)) & 0xff;
	else if (size == 2)
		*val = (data >> ((where & 3) << 3)) & 0xffff;
	else
		*val = data;

	return PCIBIOS_SUCCESSFUL;
}