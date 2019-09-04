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

/* Variables and functions */
 unsigned long IORESOURCE_IO ; 
 unsigned long IORESOURCE_MEM ; 
 unsigned long IORESOURCE_PREFETCH ; 

__attribute__((used)) static unsigned long of_bus_pci_get_flags(const u32 *addr, unsigned long flags)
{
	u32 w = addr[0];

	/* For PCI, we override whatever child busses may have used.  */
	flags = 0;
	switch((w >> 24) & 0x03) {
	case 0x01:
		flags |= IORESOURCE_IO;
		break;

	case 0x02: /* 32 bits */
	case 0x03: /* 64 bits */
		flags |= IORESOURCE_MEM;
		break;
	}
	if (w & 0x40000000)
		flags |= IORESOURCE_PREFETCH;
	return flags;
}