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
struct ttm_tt {unsigned int num_pages; struct page** pages; } ;
struct page {int dummy; } ;
struct amdgpu_ttm_tt {int userflags; } ;

/* Variables and functions */
 int AMDGPU_GEM_USERPTR_READONLY ; 
 int /*<<< orphan*/  mark_page_accessed (struct page*) ; 
 int /*<<< orphan*/  set_page_dirty (struct page*) ; 

void amdgpu_ttm_tt_mark_user_pages(struct ttm_tt *ttm)
{
	struct amdgpu_ttm_tt *gtt = (void *)ttm;
	unsigned i;

	for (i = 0; i < ttm->num_pages; ++i) {
		struct page *page = ttm->pages[i];

		if (!page)
			continue;

		if (!(gtt->userflags & AMDGPU_GEM_USERPTR_READONLY))
			set_page_dirty(page);

		mark_page_accessed(page);
	}
}