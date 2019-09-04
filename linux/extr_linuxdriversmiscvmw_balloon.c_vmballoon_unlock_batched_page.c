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
typedef  int u64 ;
typedef  scalar_t__ u16 ;
struct vmballoon_page_size {int /*<<< orphan*/  pages; } ;
struct TYPE_2__ {int /*<<< orphan*/ * free; } ;
struct vmballoon {int /*<<< orphan*/  size; TYPE_1__ stats; int /*<<< orphan*/  batch_page; struct vmballoon_page_size* page_sizes; } ;
struct page {int /*<<< orphan*/  lru; } ;

/* Variables and functions */
 int EIO ; 
 int PAGE_SHIFT ; 
 int /*<<< orphan*/  STATS_INC (int /*<<< orphan*/ ) ; 
 int VMW_BALLOON_SUCCESS ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct page* pfn_to_page (int) ; 
 int vmballoon_batch_get_pa (int /*<<< orphan*/ ,int) ; 
 int vmballoon_batch_get_status (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  vmballoon_free_page (struct page*,int) ; 
 scalar_t__ vmballoon_page_size (int) ; 
 int vmballoon_send_batched_unlock (struct vmballoon*,unsigned int,int,unsigned int*) ; 

__attribute__((used)) static int vmballoon_unlock_batched_page(struct vmballoon *b,
				unsigned int num_pages, bool is_2m_pages,
				unsigned int *target)
{
	int locked, i, ret = 0;
	bool hv_success;
	u16 size_per_page = vmballoon_page_size(is_2m_pages);

	hv_success = vmballoon_send_batched_unlock(b, num_pages, is_2m_pages,
			target);
	if (!hv_success)
		ret = -EIO;

	for (i = 0; i < num_pages; i++) {
		u64 pa = vmballoon_batch_get_pa(b->batch_page, i);
		struct page *p = pfn_to_page(pa >> PAGE_SHIFT);
		struct vmballoon_page_size *page_size =
				&b->page_sizes[is_2m_pages];

		locked = vmballoon_batch_get_status(b->batch_page, i);
		if (!hv_success || locked != VMW_BALLOON_SUCCESS) {
			/*
			 * That page wasn't successfully unlocked by the
			 * hypervisor, re-add it to the list of pages owned by
			 * the balloon driver.
			 */
			list_add(&p->lru, &page_size->pages);
		} else {
			/* deallocate page */
			vmballoon_free_page(p, is_2m_pages);
			STATS_INC(b->stats.free[is_2m_pages]);

			/* update balloon size */
			b->size -= size_per_page;
		}
	}

	return ret;
}