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
 int /*<<< orphan*/  ClearPageReserved (struct page*) ; 
 int /*<<< orphan*/  __free_pages (struct page*,unsigned long) ; 
 unsigned long get_order (unsigned long) ; 
 struct page* virt_to_page (unsigned long) ; 

__attribute__((used)) static void fadump_cpu_notes_buf_free(unsigned long vaddr, unsigned long size)
{
	struct page *page;
	unsigned long order, count, i;

	order = get_order(size);
	count = 1 << order;
	page = virt_to_page(vaddr);
	for (i = 0; i < count; i++)
		ClearPageReserved(page + i);
	__free_pages(page, order);
}