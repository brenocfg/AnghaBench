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
 int /*<<< orphan*/  __pa (void*) ; 
 int /*<<< orphan*/  copy_page_asm (void*,void*) ; 
 int /*<<< orphan*/  flush_dcache_page_asm (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  preempt_disable () ; 
 int /*<<< orphan*/  preempt_enable () ; 

void copy_user_page(void *vto, void *vfrom, unsigned long vaddr,
	struct page *pg)
{
       /* Copy using kernel mapping.  No coherency is needed (all in
	  kunmap) for the `to' page.  However, the `from' page needs to
	  be flushed through a mapping equivalent to the user mapping
	  before it can be accessed through the kernel mapping. */
	preempt_disable();
	flush_dcache_page_asm(__pa(vfrom), vaddr);
	copy_page_asm(vto, vfrom);
	preempt_enable();
}