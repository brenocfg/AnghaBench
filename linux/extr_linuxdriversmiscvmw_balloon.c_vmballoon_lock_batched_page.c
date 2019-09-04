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
typedef  int u64 ;
typedef  int /*<<< orphan*/  u16 ;
struct vmballoon_page_size {int /*<<< orphan*/  n_refused_pages; int /*<<< orphan*/  refused_pages; int /*<<< orphan*/  pages; } ;
struct vmballoon {int /*<<< orphan*/  size; int /*<<< orphan*/  batch_page; struct vmballoon_page_size* page_sizes; } ;
struct page {int /*<<< orphan*/  lru; } ;

/* Variables and functions */
 int EIO ; 
 int PAGE_SHIFT ; 
#define  VMW_BALLOON_ERROR_PPN_INVALID 132 
#define  VMW_BALLOON_ERROR_PPN_NOTNEEDED 131 
#define  VMW_BALLOON_ERROR_PPN_PINNED 130 
#define  VMW_BALLOON_ERROR_RESET 129 
 int /*<<< orphan*/  VMW_BALLOON_MAX_REFUSED ; 
#define  VMW_BALLOON_SUCCESS 128 
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct page* pfn_to_page (int) ; 
 int vmballoon_batch_get_pa (int /*<<< orphan*/ ,int) ; 
 int vmballoon_batch_get_status (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  vmballoon_free_page (struct page*,int) ; 
 int /*<<< orphan*/  vmballoon_page_size (int) ; 
 int vmballoon_send_batched_lock (struct vmballoon*,unsigned int,int,unsigned int*) ; 

__attribute__((used)) static int vmballoon_lock_batched_page(struct vmballoon *b,
		unsigned int num_pages, bool is_2m_pages, unsigned int *target)
{
	int locked, i;
	u16 size_per_page = vmballoon_page_size(is_2m_pages);

	locked = vmballoon_send_batched_lock(b, num_pages, is_2m_pages,
			target);
	if (locked > 0) {
		for (i = 0; i < num_pages; i++) {
			u64 pa = vmballoon_batch_get_pa(b->batch_page, i);
			struct page *p = pfn_to_page(pa >> PAGE_SHIFT);

			vmballoon_free_page(p, is_2m_pages);
		}

		return -EIO;
	}

	for (i = 0; i < num_pages; i++) {
		u64 pa = vmballoon_batch_get_pa(b->batch_page, i);
		struct page *p = pfn_to_page(pa >> PAGE_SHIFT);
		struct vmballoon_page_size *page_size =
				&b->page_sizes[is_2m_pages];

		locked = vmballoon_batch_get_status(b->batch_page, i);

		switch (locked) {
		case VMW_BALLOON_SUCCESS:
			list_add(&p->lru, &page_size->pages);
			b->size += size_per_page;
			break;
		case VMW_BALLOON_ERROR_PPN_PINNED:
		case VMW_BALLOON_ERROR_PPN_INVALID:
			if (page_size->n_refused_pages
					< VMW_BALLOON_MAX_REFUSED) {
				list_add(&p->lru, &page_size->refused_pages);
				page_size->n_refused_pages++;
				break;
			}
			/* Fallthrough */
		case VMW_BALLOON_ERROR_RESET:
		case VMW_BALLOON_ERROR_PPN_NOTNEEDED:
			vmballoon_free_page(p, is_2m_pages);
			break;
		default:
			/* This should never happen */
			WARN_ON_ONCE(true);
		}
	}

	return 0;
}