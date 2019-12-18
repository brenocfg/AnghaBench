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
typedef  scalar_t__ u32 ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ PAGE_ALIGN (scalar_t__) ; 
 scalar_t__ PAGE_SIZE ; 
 int /*<<< orphan*/  SetPageReserved (int /*<<< orphan*/ ) ; 
 unsigned long __get_free_pages (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ get_order (scalar_t__) ; 
 int /*<<< orphan*/  virt_to_page (unsigned long) ; 
 scalar_t__ virt_to_phys (void*) ; 

unsigned long omap_vout_alloc_buffer(u32 buf_size, u32 *phys_addr)
{
	u32 order, size;
	unsigned long virt_addr, addr;

	size = PAGE_ALIGN(buf_size);
	order = get_order(size);
	virt_addr = __get_free_pages(GFP_KERNEL, order);
	addr = virt_addr;

	if (virt_addr) {
		while (size > 0) {
			SetPageReserved(virt_to_page(addr));
			addr += PAGE_SIZE;
			size -= PAGE_SIZE;
		}
	}
	*phys_addr = (u32) virt_to_phys((void *) virt_addr);
	return virt_addr;
}