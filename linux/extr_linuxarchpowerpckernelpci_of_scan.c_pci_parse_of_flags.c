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
 unsigned int IORESOURCE_IO ; 
 unsigned int IORESOURCE_MEM ; 
 unsigned int IORESOURCE_PREFETCH ; 
 unsigned int IORESOURCE_READONLY ; 
 unsigned int IORESOURCE_SIZEALIGN ; 
 unsigned int PCI_BASE_ADDRESS_MEM_PREFETCH ; 
 int PCI_BASE_ADDRESS_MEM_TYPE_1M ; 
 int PCI_BASE_ADDRESS_MEM_TYPE_64 ; 
 unsigned int PCI_BASE_ADDRESS_SPACE_IO ; 
 unsigned int PCI_BASE_ADDRESS_SPACE_MEMORY ; 

unsigned int pci_parse_of_flags(u32 addr0, int bridge)
{
	unsigned int flags = 0;

	if (addr0 & 0x02000000) {
		flags = IORESOURCE_MEM | PCI_BASE_ADDRESS_SPACE_MEMORY;
		flags |= (addr0 >> 22) & PCI_BASE_ADDRESS_MEM_TYPE_64;
		flags |= (addr0 >> 28) & PCI_BASE_ADDRESS_MEM_TYPE_1M;
		if (addr0 & 0x40000000)
			flags |= IORESOURCE_PREFETCH
				 | PCI_BASE_ADDRESS_MEM_PREFETCH;
		/* Note: We don't know whether the ROM has been left enabled
		 * by the firmware or not. We mark it as disabled (ie, we do
		 * not set the IORESOURCE_ROM_ENABLE flag) for now rather than
		 * do a config space read, it will be force-enabled if needed
		 */
		if (!bridge && (addr0 & 0xff) == 0x30)
			flags |= IORESOURCE_READONLY;
	} else if (addr0 & 0x01000000)
		flags = IORESOURCE_IO | PCI_BASE_ADDRESS_SPACE_IO;
	if (flags)
		flags |= IORESOURCE_SIZEALIGN;
	return flags;
}