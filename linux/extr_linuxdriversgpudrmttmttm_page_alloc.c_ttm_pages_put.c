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
 int /*<<< orphan*/  __free_pages (struct page*,unsigned int) ; 
 int /*<<< orphan*/  pr_err (char*,unsigned int) ; 
 scalar_t__ ttm_set_pages_array_wb (struct page**,unsigned int) ; 
 scalar_t__ ttm_set_pages_wb (struct page*,unsigned int) ; 

__attribute__((used)) static void ttm_pages_put(struct page *pages[], unsigned npages,
		unsigned int order)
{
	unsigned int i, pages_nr = (1 << order);

	if (order == 0) {
		if (ttm_set_pages_array_wb(pages, npages))
			pr_err("Failed to set %d pages to wb!\n", npages);
	}

	for (i = 0; i < npages; ++i) {
		if (order > 0) {
			if (ttm_set_pages_wb(pages[i], pages_nr))
				pr_err("Failed to set %d pages to wb!\n", pages_nr);
		}
		__free_pages(pages[i], order);
	}
}