#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u64 ;
struct TYPE_3__ {unsigned long start; scalar_t__ attribute; scalar_t__ num_pages; } ;
typedef  TYPE_1__ kern_memdesc_t ;
typedef  scalar_t__ (* efi_freemem_callback_t ) (scalar_t__,scalar_t__,void*) ;

/* Variables and functions */
 scalar_t__ EFI_MEMORY_WB ; 
 scalar_t__ EFI_PAGE_SHIFT ; 
 scalar_t__ PAGE_ALIGN (unsigned long) ; 
 scalar_t__ PAGE_MASK ; 
 scalar_t__ PAGE_OFFSET ; 
 scalar_t__ __IA64_UNCACHED_OFFSET ; 
 TYPE_1__* kern_memmap ; 
 scalar_t__ stub1 (scalar_t__,scalar_t__,void*) ; 

__attribute__((used)) static void
walk (efi_freemem_callback_t callback, void *arg, u64 attr)
{
	kern_memdesc_t *k;
	u64 start, end, voff;

	voff = (attr == EFI_MEMORY_WB) ? PAGE_OFFSET : __IA64_UNCACHED_OFFSET;
	for (k = kern_memmap; k->start != ~0UL; k++) {
		if (k->attribute != attr)
			continue;
		start = PAGE_ALIGN(k->start);
		end = (k->start + (k->num_pages << EFI_PAGE_SHIFT)) & PAGE_MASK;
		if (start < end)
			if ((*callback)(start + voff, end + voff, arg) < 0)
				return;
	}
}