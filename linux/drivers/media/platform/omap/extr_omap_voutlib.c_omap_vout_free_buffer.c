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
 int /*<<< orphan*/  ClearPageReserved (int /*<<< orphan*/ ) ; 
 scalar_t__ PAGE_ALIGN (scalar_t__) ; 
 scalar_t__ PAGE_SIZE ; 
 int /*<<< orphan*/  free_pages (unsigned long,scalar_t__) ; 
 scalar_t__ get_order (scalar_t__) ; 
 int /*<<< orphan*/  virt_to_page (unsigned long) ; 

void omap_vout_free_buffer(unsigned long virtaddr, u32 buf_size)
{
	u32 order, size;
	unsigned long addr = virtaddr;

	size = PAGE_ALIGN(buf_size);
	order = get_order(size);

	while (size > 0) {
		ClearPageReserved(virt_to_page(addr));
		addr += PAGE_SIZE;
		size -= PAGE_SIZE;
	}
	free_pages((unsigned long) virtaddr, order);
}