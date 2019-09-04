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
 scalar_t__ PAGE_SIZE ; 
 int /*<<< orphan*/  __flush_dcache (unsigned long,scalar_t__) ; 
 int /*<<< orphan*/  __flush_icache (unsigned long,scalar_t__) ; 
 int /*<<< orphan*/  clear_page (void*) ; 

void clear_user_page(void *addr, unsigned long vaddr, struct page *page)
{
	__flush_dcache(vaddr, vaddr + PAGE_SIZE);
	__flush_icache(vaddr, vaddr + PAGE_SIZE);
	clear_page(addr);
	__flush_dcache((unsigned long)addr, (unsigned long)addr + PAGE_SIZE);
	__flush_icache((unsigned long)addr, (unsigned long)addr + PAGE_SIZE);
}