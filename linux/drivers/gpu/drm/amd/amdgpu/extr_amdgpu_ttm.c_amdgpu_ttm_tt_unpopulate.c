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
struct ttm_tt {int page_flags; int /*<<< orphan*/  bdev; int /*<<< orphan*/  sg; } ;
struct amdgpu_ttm_tt {int /*<<< orphan*/  ttm; scalar_t__ userptr; } ;
struct amdgpu_device {int /*<<< orphan*/  dev; scalar_t__ need_swiotlb; } ;

/* Variables and functions */
 int TTM_PAGE_FLAG_SG ; 
 struct amdgpu_device* amdgpu_ttm_adev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  amdgpu_ttm_tt_set_user_pages (struct ttm_tt*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 scalar_t__ swiotlb_nr_tbl () ; 
 int /*<<< orphan*/  ttm_dma_unpopulate (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ttm_unmap_and_unpopulate_pages (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void amdgpu_ttm_tt_unpopulate(struct ttm_tt *ttm)
{
	struct amdgpu_device *adev;
	struct amdgpu_ttm_tt *gtt = (void *)ttm;
	bool slave = !!(ttm->page_flags & TTM_PAGE_FLAG_SG);

	if (gtt && gtt->userptr) {
		amdgpu_ttm_tt_set_user_pages(ttm, NULL);
		kfree(ttm->sg);
		ttm->page_flags &= ~TTM_PAGE_FLAG_SG;
		return;
	}

	if (slave)
		return;

	adev = amdgpu_ttm_adev(ttm->bdev);

#ifdef CONFIG_SWIOTLB
	if (adev->need_swiotlb && swiotlb_nr_tbl()) {
		ttm_dma_unpopulate(&gtt->ttm, adev->dev);
		return;
	}
#endif

	/* fall back to generic helper to unmap and unpopulate array */
	ttm_unmap_and_unpopulate_pages(adev->dev, &gtt->ttm);
}