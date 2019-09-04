#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct vmballoon_page_size {int /*<<< orphan*/  pages; } ;
struct TYPE_2__ {int /*<<< orphan*/ * free; } ;
struct vmballoon {int /*<<< orphan*/  size; TYPE_1__ stats; struct vmballoon_page_size* page_sizes; struct page* page; } ;
struct page {int /*<<< orphan*/  lru; } ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  STATS_INC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  page_to_pfn (struct page*) ; 
 int /*<<< orphan*/  vmballoon_free_page (struct page*,int) ; 
 int /*<<< orphan*/  vmballoon_send_unlock_page (struct vmballoon*,int /*<<< orphan*/ ,unsigned int*) ; 

__attribute__((used)) static int vmballoon_unlock_page(struct vmballoon *b, unsigned int num_pages,
		bool is_2m_pages, unsigned int *target)
{
	struct page *page = b->page;
	struct vmballoon_page_size *page_size = &b->page_sizes[false];

	/* is_2m_pages can never happen as 2m pages support implies batching */

	if (!vmballoon_send_unlock_page(b, page_to_pfn(page), target)) {
		list_add(&page->lru, &page_size->pages);
		return -EIO;
	}

	/* deallocate page */
	vmballoon_free_page(page, false);
	STATS_INC(b->stats.free[false]);

	/* update balloon size */
	b->size--;

	return 0;
}