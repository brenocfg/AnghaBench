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
struct page {int /*<<< orphan*/  flags; } ;
struct address_space {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  PG_dcache_dirty ; 
 struct page* ZERO_PAGE (int /*<<< orphan*/ ) ; 
 int dcache_dirty_cpu (struct page*) ; 
 int /*<<< orphan*/  flush_dcache_page_impl (struct page*) ; 
 int get_cpu () ; 
 scalar_t__ hypervisor ; 
 int /*<<< orphan*/  mapping_mapped (struct address_space*) ; 
 struct address_space* page_mapping_file (struct page*) ; 
 int /*<<< orphan*/  put_cpu () ; 
 int /*<<< orphan*/  set_dcache_dirty (struct page*,int) ; 
 int /*<<< orphan*/  smp_flush_dcache_page_impl (struct page*,int) ; 
 int test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ tlb_type ; 

void flush_dcache_page(struct page *page)
{
	struct address_space *mapping;
	int this_cpu;

	if (tlb_type == hypervisor)
		return;

	/* Do not bother with the expensive D-cache flush if it
	 * is merely the zero page.  The 'bigcore' testcase in GDB
	 * causes this case to run millions of times.
	 */
	if (page == ZERO_PAGE(0))
		return;

	this_cpu = get_cpu();

	mapping = page_mapping_file(page);
	if (mapping && !mapping_mapped(mapping)) {
		int dirty = test_bit(PG_dcache_dirty, &page->flags);
		if (dirty) {
			int dirty_cpu = dcache_dirty_cpu(page);

			if (dirty_cpu == this_cpu)
				goto out;
			smp_flush_dcache_page_impl(page, dirty_cpu);
		}
		set_dcache_dirty(page, this_cpu);
	} else {
		/* We could delay the flush for the !page_mapping
		 * case too.  But that case is for exec env/arg
		 * pages and those are %99 certainly going to get
		 * faulted into the tlb (and thus flushed) anyways.
		 */
		flush_dcache_page_impl(page);
	}

out:
	put_cpu();
}