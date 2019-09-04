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
typedef  int u8 ;
typedef  int u32 ;
struct pci_bus {int dummy; } ;

/* Variables and functions */
 int PCIBIOS_SUCCESSFUL ; 
 int /*<<< orphan*/  PCI_ACCESS_READ ; 
 int /*<<< orphan*/  PCI_ACCESS_WRITE ; 
 scalar_t__ config_access (int /*<<< orphan*/ ,struct pci_bus*,unsigned int,int,int*) ; 

__attribute__((used)) static int write_config_byte(struct pci_bus *bus, unsigned int devfn,
			     int where, u8 val)
{
	u32 data = 0;

	if (config_access(PCI_ACCESS_READ, bus, devfn, where, &data))
		return -1;

	data = (data & ~(0xff << ((where & 3) << 3))) |
	       (val << ((where & 3) << 3));

	if (config_access(PCI_ACCESS_WRITE, bus, devfn, where, &data))
		return -1;

	return PCIBIOS_SUCCESSFUL;
}