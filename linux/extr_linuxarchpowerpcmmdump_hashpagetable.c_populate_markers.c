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
struct TYPE_2__ {int /*<<< orphan*/  start_address; } ;

/* Variables and functions */
 int /*<<< orphan*/  IOREMAP_BASE ; 
 int /*<<< orphan*/  IOREMAP_END ; 
 int /*<<< orphan*/  ISA_IO_BASE ; 
 int /*<<< orphan*/  ISA_IO_END ; 
 int /*<<< orphan*/  PAGE_OFFSET ; 
 int /*<<< orphan*/  PHB_IO_BASE ; 
 int /*<<< orphan*/  PHB_IO_END ; 
 int /*<<< orphan*/  VMALLOC_END ; 
 int /*<<< orphan*/  VMALLOC_START ; 
 int /*<<< orphan*/  VMEMMAP_BASE ; 
 TYPE_1__* address_markers ; 

__attribute__((used)) static void populate_markers(void)
{
	address_markers[0].start_address = PAGE_OFFSET;
	address_markers[1].start_address = VMALLOC_START;
	address_markers[2].start_address = VMALLOC_END;
	address_markers[3].start_address = ISA_IO_BASE;
	address_markers[4].start_address = ISA_IO_END;
	address_markers[5].start_address = PHB_IO_BASE;
	address_markers[6].start_address = PHB_IO_END;
	address_markers[7].start_address = IOREMAP_BASE;
	address_markers[8].start_address = IOREMAP_END;
#ifdef CONFIG_PPC_BOOK3S_64
	address_markers[9].start_address =  H_VMEMMAP_BASE;
#else
	address_markers[9].start_address =  VMEMMAP_BASE;
#endif
}