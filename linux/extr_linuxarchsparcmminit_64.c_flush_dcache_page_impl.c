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
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  __flush_icache_page (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __pa (int /*<<< orphan*/ ) ; 
 scalar_t__ hypervisor ; 
 int /*<<< orphan*/  page_address (struct page*) ; 
 int /*<<< orphan*/ * page_mapping_file (struct page*) ; 
 scalar_t__ spitfire ; 
 scalar_t__ tlb_type ; 

inline void flush_dcache_page_impl(struct page *page)
{
	BUG_ON(tlb_type == hypervisor);
#ifdef CONFIG_DEBUG_DCFLUSH
	atomic_inc(&dcpage_flushes);
#endif

#ifdef DCACHE_ALIASING_POSSIBLE
	__flush_dcache_page(page_address(page),
			    ((tlb_type == spitfire) &&
			     page_mapping_file(page) != NULL));
#else
	if (page_mapping_file(page) != NULL &&
	    tlb_type == spitfire)
		__flush_icache_page(__pa(page_address(page)));
#endif
}