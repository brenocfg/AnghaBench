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
 int /*<<< orphan*/  FIXADDR_START ; 
 int /*<<< orphan*/  FIXADDR_TOP ; 
 int /*<<< orphan*/  IOREMAP_TOP ; 
 int /*<<< orphan*/  PAGE_OFFSET ; 
 int /*<<< orphan*/  VMALLOC_END ; 
 int /*<<< orphan*/  VMALLOC_START ; 
 TYPE_1__* address_markers ; 
 int /*<<< orphan*/  ioremap_bot ; 

__attribute__((used)) static void populate_markers(void)
{
	int i = 0;

	address_markers[i++].start_address = PAGE_OFFSET;
	address_markers[i++].start_address = VMALLOC_START;
	address_markers[i++].start_address = VMALLOC_END;
#ifdef CONFIG_PPC64
	address_markers[i++].start_address = ISA_IO_BASE;
	address_markers[i++].start_address = ISA_IO_END;
	address_markers[i++].start_address = PHB_IO_BASE;
	address_markers[i++].start_address = PHB_IO_END;
	address_markers[i++].start_address = IOREMAP_BASE;
	address_markers[i++].start_address = IOREMAP_END;
#ifdef CONFIG_PPC_BOOK3S_64
	address_markers[i++].start_address =  H_VMEMMAP_BASE;
#else
	address_markers[i++].start_address =  VMEMMAP_BASE;
#endif
#else /* !CONFIG_PPC64 */
	address_markers[i++].start_address = ioremap_bot;
	address_markers[i++].start_address = IOREMAP_TOP;
#ifdef CONFIG_NOT_COHERENT_CACHE
	address_markers[i++].start_address = IOREMAP_TOP;
	address_markers[i++].start_address = IOREMAP_TOP +
					     CONFIG_CONSISTENT_SIZE;
#endif
#ifdef CONFIG_HIGHMEM
	address_markers[i++].start_address = PKMAP_BASE;
	address_markers[i++].start_address = PKMAP_ADDR(LAST_PKMAP);
#endif
	address_markers[i++].start_address = FIXADDR_START;
	address_markers[i++].start_address = FIXADDR_TOP;
#endif /* CONFIG_PPC64 */
}