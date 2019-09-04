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
 int /*<<< orphan*/  DBG (char*) ; 

__attribute__((used)) static int
mk_conf_addr(struct pci_bus *pbus, unsigned int device_fn, int where,
	     unsigned long *pci_addr, unsigned char *type1)
{
	unsigned long addr;
	u8 bus = pbus->number;

	DBG(("mk_conf_addr(bus=%d, dfn=0x%x, where=0x%x,"
	     " addr=0x%lx, type1=0x%x)\n",
	     bus, device_fn, where, pci_addr, type1));

	if (bus == 0) {
		int device = device_fn >> 3;

		/* Type 0 configuration cycle.  */

		if (device > 8) {
			DBG(("mk_conf_addr: device (%d)>20, returning -1\n",
			     device));
			return -1;
		}

		*type1 = 0;
		addr = (0x0800L << device) | ((device_fn & 7) << 8) | (where);
	} else {
		/* Type 1 configuration cycle.  */
		*type1 = 1;
		addr = (bus << 16) | (device_fn << 8) | (where);
	}
	*pci_addr = addr;
	DBG(("mk_conf_addr: returning pci_addr 0x%lx\n", addr));
	return 0;
}