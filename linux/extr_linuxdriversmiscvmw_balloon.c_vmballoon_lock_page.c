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
struct vmballoon_page_size {scalar_t__ n_refused_pages; int /*<<< orphan*/  pages; int /*<<< orphan*/  refused_pages; } ;
struct TYPE_2__ {int /*<<< orphan*/ * refused_alloc; } ;
struct vmballoon {int /*<<< orphan*/  size; TYPE_1__ stats; struct vmballoon_page_size* page_sizes; struct page* page; } ;
struct page {int /*<<< orphan*/  lru; } ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  STATS_INC (int /*<<< orphan*/ ) ; 
 int VMW_BALLOON_ERROR_PPN_NOTNEEDED ; 
 int VMW_BALLOON_ERROR_RESET ; 
 scalar_t__ VMW_BALLOON_MAX_REFUSED ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  page_to_pfn (struct page*) ; 
 int /*<<< orphan*/  vmballoon_free_page (struct page*,int) ; 
 int vmballoon_send_lock_page (struct vmballoon*,int /*<<< orphan*/ ,int*,unsigned int*) ; 

__attribute__((used)) static int vmballoon_lock_page(struct vmballoon *b, unsigned int num_pages,
				bool is_2m_pages, unsigned int *target)
{
	int locked, hv_status;
	struct page *page = b->page;
	struct vmballoon_page_size *page_size = &b->page_sizes[false];

	/* is_2m_pages can never happen as 2m pages support implies batching */

	locked = vmballoon_send_lock_page(b, page_to_pfn(page), &hv_status,
								target);
	if (locked) {
		STATS_INC(b->stats.refused_alloc[false]);

		if (locked == -EIO &&
		    (hv_status == VMW_BALLOON_ERROR_RESET ||
		     hv_status == VMW_BALLOON_ERROR_PPN_NOTNEEDED)) {
			vmballoon_free_page(page, false);
			return -EIO;
		}

		/*
		 * Place page on the list of non-balloonable pages
		 * and retry allocation, unless we already accumulated
		 * too many of them, in which case take a breather.
		 */
		if (page_size->n_refused_pages < VMW_BALLOON_MAX_REFUSED) {
			page_size->n_refused_pages++;
			list_add(&page->lru, &page_size->refused_pages);
		} else {
			vmballoon_free_page(page, false);
		}
		return locked;
	}

	/* track allocated page */
	list_add(&page->lru, &page_size->pages);

	/* update balloon size */
	b->size++;

	return 0;
}