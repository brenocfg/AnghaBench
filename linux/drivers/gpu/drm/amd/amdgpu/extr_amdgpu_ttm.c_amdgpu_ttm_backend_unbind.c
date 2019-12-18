#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct ttm_tt {int /*<<< orphan*/  num_pages; int /*<<< orphan*/  bdev; } ;
struct TYPE_3__ {int /*<<< orphan*/  num_pages; } ;
struct TYPE_4__ {TYPE_1__ ttm; } ;
struct amdgpu_ttm_tt {scalar_t__ offset; TYPE_2__ ttm; scalar_t__ userptr; } ;
struct amdgpu_device {int dummy; } ;

/* Variables and functions */
 scalar_t__ AMDGPU_BO_INVALID_OFFSET ; 
 int /*<<< orphan*/  DRM_ERROR (char*,int /*<<< orphan*/ ,scalar_t__) ; 
 int amdgpu_gart_unbind (struct amdgpu_device*,scalar_t__,int /*<<< orphan*/ ) ; 
 struct amdgpu_device* amdgpu_ttm_adev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  amdgpu_ttm_tt_unpin_userptr (struct ttm_tt*) ; 

__attribute__((used)) static int amdgpu_ttm_backend_unbind(struct ttm_tt *ttm)
{
	struct amdgpu_device *adev = amdgpu_ttm_adev(ttm->bdev);
	struct amdgpu_ttm_tt *gtt = (void *)ttm;
	int r;

	/* if the pages have userptr pinning then clear that first */
	if (gtt->userptr)
		amdgpu_ttm_tt_unpin_userptr(ttm);

	if (gtt->offset == AMDGPU_BO_INVALID_OFFSET)
		return 0;

	/* unbind shouldn't be done for GDS/GWS/OA in ttm_bo_clean_mm */
	r = amdgpu_gart_unbind(adev, gtt->offset, ttm->num_pages);
	if (r)
		DRM_ERROR("failed to unbind %lu pages at 0x%08llX\n",
			  gtt->ttm.ttm.num_pages, gtt->offset);
	return r;
}