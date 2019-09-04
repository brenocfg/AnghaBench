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

/* Variables and functions */
 unsigned long PAGE_MASK ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 void* module_alloc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_memory_ro (unsigned long,int) ; 

void *alloc_insn_page(void)
{
	void *page;

	page = module_alloc(PAGE_SIZE);
	if (page)
		set_memory_ro((unsigned long)page & PAGE_MASK, 1);

	return page;
}