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
 unsigned long FIXADDR_START ; 
 unsigned long PAGE_MASK ; 
 int /*<<< orphan*/  flush_tlb_all () ; 
 scalar_t__ unlikely (int) ; 
 void vfree (void*) ; 

void iounmap(void *addr)
{
	/* If the page is from the fixmap pool then we just clear out
	 * the fixmap mapping.
	 */
	if (unlikely((unsigned long)addr > FIXADDR_START)) {
		/* This is a bit broken... we don't really know
		 * how big the area is so it's difficult to know
		 * how many fixed pages to invalidate...
		 * just flush tlb and hope for the best...
		 * consider this a FIXME
		 *
		 * Really we should be clearing out one or more page
		 * table entries for these virtual addresses so that
		 * future references cause a page fault... for now, we
		 * rely on two things:
		 *   i)  this code never gets called on known boards
		 *   ii) invalid accesses to the freed areas aren't made
		 */
		flush_tlb_all();
		return;
	}

	return vfree((void *)(PAGE_MASK & (unsigned long)addr));
}