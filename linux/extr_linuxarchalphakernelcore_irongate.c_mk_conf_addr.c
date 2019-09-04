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
struct pci_bus {int number; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG_CFG (char*) ; 
 unsigned long IRONGATE_CONF ; 

__attribute__((used)) static int
mk_conf_addr(struct pci_bus *pbus, unsigned int device_fn, int where,
	     unsigned long *pci_addr, unsigned char *type1)
{
	unsigned long addr;
	u8 bus = pbus->number;

	DBG_CFG(("mk_conf_addr(bus=%d ,device_fn=0x%x, where=0x%x, "
		 "pci_addr=0x%p, type1=0x%p)\n",
		 bus, device_fn, where, pci_addr, type1));

	*type1 = (bus != 0);

	addr = (bus << 16) | (device_fn << 8) | where;
	addr |= IRONGATE_CONF;

	*pci_addr = addr;
	DBG_CFG(("mk_conf_addr: returning pci_addr 0x%lx\n", addr));
	return 0;
}