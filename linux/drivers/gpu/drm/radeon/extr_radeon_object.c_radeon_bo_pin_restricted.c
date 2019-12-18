#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u64 ;
typedef  scalar_t__ u32 ;
struct ttm_operation_ctx {int member_0; int member_1; } ;
struct TYPE_10__ {int num_placement; } ;
struct TYPE_9__ {int /*<<< orphan*/  ttm; } ;
struct radeon_bo {int pin_count; int flags; TYPE_3__* rdev; TYPE_5__ placement; TYPE_4__ tbo; TYPE_2__* placements; scalar_t__ prime_shared_count; } ;
struct TYPE_6__ {scalar_t__ vram_start; scalar_t__ gtt_start; scalar_t__ visible_vram_size; } ;
struct TYPE_8__ {int /*<<< orphan*/  dev; int /*<<< orphan*/  gart_pin_size; int /*<<< orphan*/  vram_pin_size; TYPE_1__ mc; } ;
struct TYPE_7__ {int flags; scalar_t__ lpfn; } ;

/* Variables and functions */
 int EINVAL ; 
 int EPERM ; 
 scalar_t__ PAGE_SHIFT ; 
 scalar_t__ RADEON_GEM_DOMAIN_VRAM ; 
 int RADEON_GEM_NO_CPU_ACCESS ; 
 int TTM_PL_FLAG_NO_EVICT ; 
 int TTM_PL_FLAG_VRAM ; 
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,struct radeon_bo*) ; 
 scalar_t__ likely (int) ; 
 scalar_t__ radeon_bo_gpu_offset (struct radeon_bo*) ; 
 scalar_t__ radeon_bo_size (struct radeon_bo*) ; 
 int /*<<< orphan*/  radeon_ttm_placement_from_domain (struct radeon_bo*,scalar_t__) ; 
 scalar_t__ radeon_ttm_tt_has_userptr (int /*<<< orphan*/ ) ; 
 int ttm_bo_validate (TYPE_4__*,TYPE_5__*,struct ttm_operation_ctx*) ; 

int radeon_bo_pin_restricted(struct radeon_bo *bo, u32 domain, u64 max_offset,
			     u64 *gpu_addr)
{
	struct ttm_operation_ctx ctx = { false, false };
	int r, i;

	if (radeon_ttm_tt_has_userptr(bo->tbo.ttm))
		return -EPERM;

	if (bo->pin_count) {
		bo->pin_count++;
		if (gpu_addr)
			*gpu_addr = radeon_bo_gpu_offset(bo);

		if (max_offset != 0) {
			u64 domain_start;

			if (domain == RADEON_GEM_DOMAIN_VRAM)
				domain_start = bo->rdev->mc.vram_start;
			else
				domain_start = bo->rdev->mc.gtt_start;
			WARN_ON_ONCE(max_offset <
				     (radeon_bo_gpu_offset(bo) - domain_start));
		}

		return 0;
	}
	if (bo->prime_shared_count && domain == RADEON_GEM_DOMAIN_VRAM) {
		/* A BO shared as a dma-buf cannot be sensibly migrated to VRAM */
		return -EINVAL;
	}

	radeon_ttm_placement_from_domain(bo, domain);
	for (i = 0; i < bo->placement.num_placement; i++) {
		/* force to pin into visible video ram */
		if ((bo->placements[i].flags & TTM_PL_FLAG_VRAM) &&
		    !(bo->flags & RADEON_GEM_NO_CPU_ACCESS) &&
		    (!max_offset || max_offset > bo->rdev->mc.visible_vram_size))
			bo->placements[i].lpfn =
				bo->rdev->mc.visible_vram_size >> PAGE_SHIFT;
		else
			bo->placements[i].lpfn = max_offset >> PAGE_SHIFT;

		bo->placements[i].flags |= TTM_PL_FLAG_NO_EVICT;
	}

	r = ttm_bo_validate(&bo->tbo, &bo->placement, &ctx);
	if (likely(r == 0)) {
		bo->pin_count = 1;
		if (gpu_addr != NULL)
			*gpu_addr = radeon_bo_gpu_offset(bo);
		if (domain == RADEON_GEM_DOMAIN_VRAM)
			bo->rdev->vram_pin_size += radeon_bo_size(bo);
		else
			bo->rdev->gart_pin_size += radeon_bo_size(bo);
	} else {
		dev_err(bo->rdev->dev, "%p pin failed\n", bo);
	}
	return r;
}