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
typedef  int /*<<< orphan*/  u64 ;
struct amdgpu_device {scalar_t__ family; } ;
struct TYPE_2__ {int /*<<< orphan*/  bdev; } ;
struct amdgpu_bo {int /*<<< orphan*/  tiling_flags; TYPE_1__ tbo; } ;

/* Variables and functions */
 scalar_t__ AMDGPU_FAMILY_CZ ; 
 int AMDGPU_TILING_GET (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int EINVAL ; 
 int /*<<< orphan*/  TILE_SPLIT ; 
 struct amdgpu_device* amdgpu_ttm_adev (int /*<<< orphan*/ ) ; 

int amdgpu_bo_set_tiling_flags(struct amdgpu_bo *bo, u64 tiling_flags)
{
	struct amdgpu_device *adev = amdgpu_ttm_adev(bo->tbo.bdev);

	if (adev->family <= AMDGPU_FAMILY_CZ &&
	    AMDGPU_TILING_GET(tiling_flags, TILE_SPLIT) > 6)
		return -EINVAL;

	bo->tiling_flags = tiling_flags;
	return 0;
}