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
struct amdgpu_ttm_tt {int /*<<< orphan*/  mmu_invalidations; int /*<<< orphan*/  last_set_pages; } ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  put_page (struct page*) ; 

void amdgpu_ttm_tt_set_user_pages(struct ttm_tt *ttm, struct page **pages)
{
	struct amdgpu_ttm_tt *gtt = (void *)ttm;
	unsigned i;

	gtt->last_set_pages = atomic_read(&gtt->mmu_invalidations);
	for (i = 0; i < ttm->num_pages; ++i) {
		if (ttm->pages[i])
			put_page(ttm->pages[i]);

		ttm->pages[i] = pages ? pages[i] : NULL;
	}
}