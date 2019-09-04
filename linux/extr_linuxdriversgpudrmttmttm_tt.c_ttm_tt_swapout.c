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
struct ttm_tt {scalar_t__ state; scalar_t__ caching_state; int num_pages; int page_flags; struct page* swap_storage; struct page** pages; } ;
struct page {struct address_space* f_mapping; } ;
struct file {struct address_space* f_mapping; } ;
struct address_space {int dummy; } ;
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int ENOMEM ; 
 scalar_t__ IS_ERR (struct page*) ; 
 int PAGE_SHIFT ; 
 int PTR_ERR (struct page*) ; 
 int TTM_PAGE_FLAG_NO_RETRY ; 
 int TTM_PAGE_FLAG_PERSISTENT_SWAP ; 
 int TTM_PAGE_FLAG_SWAPPED ; 
 int /*<<< orphan*/  __GFP_RETRY_MAYFAIL ; 
 int /*<<< orphan*/  copy_highpage (struct page*,struct page*) ; 
 int /*<<< orphan*/  fput (struct page*) ; 
 int /*<<< orphan*/  mapping_gfp_mask (struct address_space*) ; 
 int /*<<< orphan*/  mark_page_accessed (struct page*) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int /*<<< orphan*/  put_page (struct page*) ; 
 int /*<<< orphan*/  set_page_dirty (struct page*) ; 
 struct page* shmem_file_setup (char*,int,int /*<<< orphan*/ ) ; 
 struct page* shmem_read_mapping_page_gfp (struct address_space*,int,int /*<<< orphan*/ ) ; 
 scalar_t__ tt_cached ; 
 scalar_t__ tt_unbound ; 
 scalar_t__ tt_unpopulated ; 
 int /*<<< orphan*/  ttm_tt_unpopulate (struct ttm_tt*) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

int ttm_tt_swapout(struct ttm_tt *ttm, struct file *persistent_swap_storage)
{
	struct address_space *swap_space;
	struct file *swap_storage;
	struct page *from_page;
	struct page *to_page;
	int i;
	int ret = -ENOMEM;

	BUG_ON(ttm->state != tt_unbound && ttm->state != tt_unpopulated);
	BUG_ON(ttm->caching_state != tt_cached);

	if (!persistent_swap_storage) {
		swap_storage = shmem_file_setup("ttm swap",
						ttm->num_pages << PAGE_SHIFT,
						0);
		if (IS_ERR(swap_storage)) {
			pr_err("Failed allocating swap storage\n");
			return PTR_ERR(swap_storage);
		}
	} else {
		swap_storage = persistent_swap_storage;
	}

	swap_space = swap_storage->f_mapping;

	for (i = 0; i < ttm->num_pages; ++i) {
		gfp_t gfp_mask = mapping_gfp_mask(swap_space);

		gfp_mask |= (ttm->page_flags & TTM_PAGE_FLAG_NO_RETRY ? __GFP_RETRY_MAYFAIL : 0);

		from_page = ttm->pages[i];
		if (unlikely(from_page == NULL))
			continue;

		to_page = shmem_read_mapping_page_gfp(swap_space, i, gfp_mask);
		if (IS_ERR(to_page)) {
			ret = PTR_ERR(to_page);
			goto out_err;
		}
		copy_highpage(to_page, from_page);
		set_page_dirty(to_page);
		mark_page_accessed(to_page);
		put_page(to_page);
	}

	ttm_tt_unpopulate(ttm);
	ttm->swap_storage = swap_storage;
	ttm->page_flags |= TTM_PAGE_FLAG_SWAPPED;
	if (persistent_swap_storage)
		ttm->page_flags |= TTM_PAGE_FLAG_PERSISTENT_SWAP;

	return 0;
out_err:
	if (!persistent_swap_storage)
		fput(swap_storage);

	return ret;
}