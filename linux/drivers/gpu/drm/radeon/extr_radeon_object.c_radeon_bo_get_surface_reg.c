#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct radeon_surface_reg {struct radeon_bo* bo; } ;
struct radeon_device {struct radeon_surface_reg* surface_regs; } ;
struct TYPE_5__ {int start; } ;
struct TYPE_4__ {int /*<<< orphan*/  resv; } ;
struct TYPE_6__ {int num_pages; TYPE_2__ mem; TYPE_1__ base; } ;
struct radeon_bo {size_t surface_reg; scalar_t__ pin_count; TYPE_3__ tbo; int /*<<< orphan*/  pitch; int /*<<< orphan*/  tiling_flags; struct radeon_device* rdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG (char*,int,struct radeon_bo*) ; 
 int ENOMEM ; 
 int PAGE_SHIFT ; 
 int RADEON_GEM_MAX_SURFACES ; 
 int /*<<< orphan*/  dma_resv_assert_held (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  radeon_set_surface_reg (struct radeon_device*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  ttm_bo_unmap_virtual (TYPE_3__*) ; 

int radeon_bo_get_surface_reg(struct radeon_bo *bo)
{
	struct radeon_device *rdev = bo->rdev;
	struct radeon_surface_reg *reg;
	struct radeon_bo *old_object;
	int steal;
	int i;

	dma_resv_assert_held(bo->tbo.base.resv);

	if (!bo->tiling_flags)
		return 0;

	if (bo->surface_reg >= 0) {
		reg = &rdev->surface_regs[bo->surface_reg];
		i = bo->surface_reg;
		goto out;
	}

	steal = -1;
	for (i = 0; i < RADEON_GEM_MAX_SURFACES; i++) {

		reg = &rdev->surface_regs[i];
		if (!reg->bo)
			break;

		old_object = reg->bo;
		if (old_object->pin_count == 0)
			steal = i;
	}

	/* if we are all out */
	if (i == RADEON_GEM_MAX_SURFACES) {
		if (steal == -1)
			return -ENOMEM;
		/* find someone with a surface reg and nuke their BO */
		reg = &rdev->surface_regs[steal];
		old_object = reg->bo;
		/* blow away the mapping */
		DRM_DEBUG("stealing surface reg %d from %p\n", steal, old_object);
		ttm_bo_unmap_virtual(&old_object->tbo);
		old_object->surface_reg = -1;
		i = steal;
	}

	bo->surface_reg = i;
	reg->bo = bo;

out:
	radeon_set_surface_reg(rdev, i, bo->tiling_flags, bo->pitch,
			       bo->tbo.mem.start << PAGE_SHIFT,
			       bo->tbo.num_pages << PAGE_SHIFT);
	return 0;
}