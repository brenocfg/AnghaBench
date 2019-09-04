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
struct pci_bus {scalar_t__ number; } ;

/* Variables and functions */
 int /*<<< orphan*/  PCI_ACCESS_READ ; 
 int PCI_SLOT (unsigned int) ; 
 int PCI_VENDOR_ID ; 
 int config_access (int /*<<< orphan*/ ,struct pci_bus*,unsigned int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  msleep (int) ; 

__attribute__((used)) static int read_config_dword(struct pci_bus *bus, unsigned int devfn,
			     int where, u32 *val)
{
	int ret;
	int delay = 1;

	/*
	 * Don't scan too far, else there will be errors with plugged in
	 * daughterboard (rb564).
	 */
	if (bus->number == 0 && PCI_SLOT(devfn) > 21)
		return 0;

retry:
	ret = config_access(PCI_ACCESS_READ, bus, devfn, where, val);

	/*
	 * Certain devices react delayed at device scan time, this
	 * gives them time to settle
	 */
	if (where == PCI_VENDOR_ID) {
		if (ret == 0xffffffff || ret == 0x00000000 ||
		    ret == 0x0000ffff || ret == 0xffff0000) {
			if (delay > 4)
				return 0;
			delay *= 2;
			msleep(delay);
			goto retry;
		}
	}

	return ret;
}