#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
typedef  int u32 ;
typedef  scalar_t__ u16 ;
struct pci_bus {int /*<<< orphan*/  number; } ;
struct ia64_sal_retval {scalar_t__ status; } ;
struct TYPE_2__ {unsigned long bs_legacy_io; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENODEV ; 
 int /*<<< orphan*/  SAL_CALL (struct ia64_sal_retval,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int,int /*<<< orphan*/ ) ; 
 TYPE_1__* SN_PCIBUS_BUSSOFT (struct pci_bus*) ; 
 int /*<<< orphan*/  SN_SAL_IOIF_PCI_SAFE ; 
 unsigned long __IA64_UNCACHED_OFFSET ; 
 int /*<<< orphan*/  __pa (int*) ; 
 int ia64_sn_probe_mem (unsigned long,long,void*) ; 
 int /*<<< orphan*/  pci_domain_nr (struct pci_bus*) ; 

int sn_pci_legacy_read(struct pci_bus *bus, u16 port, u32 *val, u8 size)
{
	unsigned long addr;
	int ret;
	struct ia64_sal_retval isrv;

	/*
	 * First, try the SN_SAL_IOIF_PCI_SAFE SAL call which can work
	 * around hw issues at the pci bus level.  SGI proms older than
	 * 4.10 don't implement this.
	 */

	SAL_CALL(isrv, SN_SAL_IOIF_PCI_SAFE,
		 pci_domain_nr(bus), bus->number,
		 0, /* io */
		 0, /* read */
		 port, size, __pa(val));

	if (isrv.status == 0)
		return size;

	/*
	 * If the above failed, retry using the SAL_PROBE call which should
	 * be present in all proms (but which cannot work round PCI chipset
	 * bugs).  This code is retained for compatibility with old
	 * pre-4.10 proms, and should be removed at some point in the future.
	 */

	if (!SN_PCIBUS_BUSSOFT(bus))
		return -ENODEV;

	addr = SN_PCIBUS_BUSSOFT(bus)->bs_legacy_io | __IA64_UNCACHED_OFFSET;
	addr += port;

	ret = ia64_sn_probe_mem(addr, (long)size, (void *)val);

	if (ret == 2)
		return -EINVAL;

	if (ret == 1)
		*val = -1;

	return size;
}