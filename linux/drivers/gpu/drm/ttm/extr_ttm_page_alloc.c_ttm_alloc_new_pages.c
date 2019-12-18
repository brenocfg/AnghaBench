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
struct page {int /*<<< orphan*/  lru; } ;
struct list_head {int dummy; } ;
typedef  int /*<<< orphan*/  gfp_t ;
typedef  enum ttm_caching_state { ____Placeholder_ttm_caching_state } ttm_caching_state ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ NUM_PAGES_TO_ALLOC ; 
 scalar_t__ PageHighMem (struct page*) ; 
 struct page* alloc_pages (int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  kfree (struct page**) ; 
 struct page** kmalloc_array (unsigned int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,struct list_head*) ; 
 unsigned int min (unsigned int,unsigned int) ; 
 int /*<<< orphan*/  pr_debug (char*,...) ; 
 int /*<<< orphan*/  ttm_handle_caching_state_failure (struct list_head*,int,int,struct page**,unsigned int) ; 
 int ttm_set_pages_caching (struct page**,int,unsigned int) ; 

__attribute__((used)) static int ttm_alloc_new_pages(struct list_head *pages, gfp_t gfp_flags,
			       int ttm_flags, enum ttm_caching_state cstate,
			       unsigned count, unsigned order)
{
	struct page **caching_array;
	struct page *p;
	int r = 0;
	unsigned i, j, cpages;
	unsigned npages = 1 << order;
	unsigned max_cpages = min(count << order, (unsigned)NUM_PAGES_TO_ALLOC);

	/* allocate array for page caching change */
	caching_array = kmalloc_array(max_cpages, sizeof(struct page *),
				      GFP_KERNEL);

	if (!caching_array) {
		pr_debug("Unable to allocate table for new pages\n");
		return -ENOMEM;
	}

	for (i = 0, cpages = 0; i < count; ++i) {
		p = alloc_pages(gfp_flags, order);

		if (!p) {
			pr_debug("Unable to get page %u\n", i);

			/* store already allocated pages in the pool after
			 * setting the caching state */
			if (cpages) {
				r = ttm_set_pages_caching(caching_array,
							  cstate, cpages);
				if (r)
					ttm_handle_caching_state_failure(pages,
						ttm_flags, cstate,
						caching_array, cpages);
			}
			r = -ENOMEM;
			goto out;
		}

		list_add(&p->lru, pages);

#ifdef CONFIG_HIGHMEM
		/* gfp flags of highmem page should never be dma32 so we
		 * we should be fine in such case
		 */
		if (PageHighMem(p))
			continue;

#endif
		for (j = 0; j < npages; ++j) {
			caching_array[cpages++] = p++;
			if (cpages == max_cpages) {

				r = ttm_set_pages_caching(caching_array,
						cstate, cpages);
				if (r) {
					ttm_handle_caching_state_failure(pages,
						ttm_flags, cstate,
						caching_array, cpages);
					goto out;
				}
				cpages = 0;
			}
		}
	}

	if (cpages) {
		r = ttm_set_pages_caching(caching_array, cstate, cpages);
		if (r)
			ttm_handle_caching_state_failure(pages,
					ttm_flags, cstate,
					caching_array, cpages);
	}
out:
	kfree(caching_array);

	return r;
}