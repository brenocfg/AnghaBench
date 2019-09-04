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
 unsigned long iop3xx_cfg_address (struct pci_bus*,unsigned int,int) ; 
 scalar_t__ iop3xx_pci_status () ; 
 int iop3xx_read (unsigned long) ; 

__attribute__((used)) static int
iop3xx_read_config(struct pci_bus *bus, unsigned int devfn, int where,
		int size, u32 *value)
{
	unsigned long addr = iop3xx_cfg_address(bus, devfn, where);
	u32 val = iop3xx_read(addr) >> ((where & 3) * 8);

	if (iop3xx_pci_status())
		val = 0xffffffff;

	*value = val;

	return PCIBIOS_SUCCESSFUL;
}