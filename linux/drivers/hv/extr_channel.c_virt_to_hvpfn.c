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
typedef  unsigned long phys_addr_t ;

/* Variables and functions */
 unsigned long PAGE_SHIFT ; 
 unsigned long __pa (void*) ; 
 scalar_t__ is_vmalloc_addr (void*) ; 
 unsigned long offset_in_page (void*) ; 
 unsigned long page_to_phys (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vmalloc_to_page (void*) ; 

__attribute__((used)) static unsigned long virt_to_hvpfn(void *addr)
{
	phys_addr_t paddr;

	if (is_vmalloc_addr(addr))
		paddr = page_to_phys(vmalloc_to_page(addr)) +
					 offset_in_page(addr);
	else
		paddr = __pa(addr);

	return  paddr >> PAGE_SHIFT;
}