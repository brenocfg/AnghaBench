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
struct page {int dummy; } ;

/* Variables and functions */
 int GFP_KERNEL ; 
 int /*<<< orphan*/  SetPageReserved (struct page*) ; 
 int __GFP_ZERO ; 
 scalar_t__ __get_free_pages (int,unsigned long) ; 
 unsigned long get_order (unsigned long) ; 
 struct page* virt_to_page (void*) ; 

__attribute__((used)) static void *fadump_cpu_notes_buf_alloc(unsigned long size)
{
	void *vaddr;
	struct page *page;
	unsigned long order, count, i;

	order = get_order(size);
	vaddr = (void *)__get_free_pages(GFP_KERNEL|__GFP_ZERO, order);
	if (!vaddr)
		return NULL;

	count = 1 << order;
	page = virt_to_page(vaddr);
	for (i = 0; i < count; i++)
		SetPageReserved(page + i);
	return vaddr;
}