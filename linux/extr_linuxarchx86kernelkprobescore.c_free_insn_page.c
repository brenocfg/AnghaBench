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
 int /*<<< orphan*/  module_memfree (void*) ; 
 int /*<<< orphan*/  set_memory_nx (unsigned long,int) ; 
 int /*<<< orphan*/  set_memory_rw (unsigned long,int) ; 

void free_insn_page(void *page)
{
	set_memory_nx((unsigned long)page & PAGE_MASK, 1);
	set_memory_rw((unsigned long)page & PAGE_MASK, 1);
	module_memfree(page);
}