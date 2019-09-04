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

/* Variables and functions */
 scalar_t__ IS_LEGACY_VGA_IOPORT (unsigned long) ; 
 int /*<<< orphan*/  IS_RUNNING_ON_SIMULATOR () ; 
 scalar_t__ SN_ACPI_BASE_SUPPORT () ; 
 unsigned long __IA64_UNCACHED_OFFSET ; 
 void* __ia64_mk_io_addr (unsigned long) ; 
 scalar_t__ is_shub2 () ; 

void *sn_io_addr(unsigned long port)
{
	if (!IS_RUNNING_ON_SIMULATOR()) {
		if (IS_LEGACY_VGA_IOPORT(port))
			return (__ia64_mk_io_addr(port));
		/* On sn2, legacy I/O ports don't point at anything */
		if (port < (64 * 1024))
			return NULL;
		if (SN_ACPI_BASE_SUPPORT())
			return (__ia64_mk_io_addr(port));
		else
			return ((void *)(port | __IA64_UNCACHED_OFFSET));
	} else {
		/* but the simulator uses them... */
		unsigned long addr;

		/*
		 * word align port, but need more than 10 bits
		 * for accessing registers in bedrock local block
		 * (so we don't do port&0xfff)
		 */
		addr = (is_shub2() ? 0xc00000028c000000UL : 0xc0000087cc000000UL) | ((port >> 2) << 12);
		if ((port >= 0x1f0 && port <= 0x1f7) || port == 0x3f6 || port == 0x3f7)
			addr |= port;
		return (void *)addr;
	}
}