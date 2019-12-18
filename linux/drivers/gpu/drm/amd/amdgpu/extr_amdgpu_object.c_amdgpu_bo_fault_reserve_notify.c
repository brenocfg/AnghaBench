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
struct ttm_operation_ctx {int member_0; int member_1; } ;
struct TYPE_4__ {scalar_t__ mem_type; unsigned long num_pages; unsigned long start; } ;
struct ttm_buffer_object {TYPE_1__ mem; int /*<<< orphan*/  bdev; } ;
struct TYPE_5__ {unsigned long visible_vram_size; } ;
struct amdgpu_device {TYPE_2__ gmc; int /*<<< orphan*/  num_vram_cpu_page_faults; } ;
struct TYPE_6__ {int num_busy_placement; int /*<<< orphan*/ * busy_placement; } ;
struct amdgpu_bo {scalar_t__ pin_count; TYPE_3__ placement; int /*<<< orphan*/ * placements; int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  AMDGPU_GEM_CREATE_CPU_ACCESS_REQUIRED ; 
 int AMDGPU_GEM_DOMAIN_GTT ; 
 int AMDGPU_GEM_DOMAIN_VRAM ; 
 int EINVAL ; 
 unsigned long PAGE_SHIFT ; 
 scalar_t__ TTM_PL_VRAM ; 
 int /*<<< orphan*/  amdgpu_bo_is_amdgpu_bo (struct ttm_buffer_object*) ; 
 int /*<<< orphan*/  amdgpu_bo_placement_from_domain (struct amdgpu_bo*,int) ; 
 struct amdgpu_device* amdgpu_ttm_adev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atomic64_inc (int /*<<< orphan*/ *) ; 
 int ttm_bo_validate (struct ttm_buffer_object*,TYPE_3__*,struct ttm_operation_ctx*) ; 
 struct amdgpu_bo* ttm_to_amdgpu_bo (struct ttm_buffer_object*) ; 
 scalar_t__ unlikely (int) ; 

int amdgpu_bo_fault_reserve_notify(struct ttm_buffer_object *bo)
{
	struct amdgpu_device *adev = amdgpu_ttm_adev(bo->bdev);
	struct ttm_operation_ctx ctx = { false, false };
	struct amdgpu_bo *abo;
	unsigned long offset, size;
	int r;

	if (!amdgpu_bo_is_amdgpu_bo(bo))
		return 0;

	abo = ttm_to_amdgpu_bo(bo);

	/* Remember that this BO was accessed by the CPU */
	abo->flags |= AMDGPU_GEM_CREATE_CPU_ACCESS_REQUIRED;

	if (bo->mem.mem_type != TTM_PL_VRAM)
		return 0;

	size = bo->mem.num_pages << PAGE_SHIFT;
	offset = bo->mem.start << PAGE_SHIFT;
	if ((offset + size) <= adev->gmc.visible_vram_size)
		return 0;

	/* Can't move a pinned BO to visible VRAM */
	if (abo->pin_count > 0)
		return -EINVAL;

	/* hurrah the memory is not visible ! */
	atomic64_inc(&adev->num_vram_cpu_page_faults);
	amdgpu_bo_placement_from_domain(abo, AMDGPU_GEM_DOMAIN_VRAM |
					AMDGPU_GEM_DOMAIN_GTT);

	/* Avoid costly evictions; only set GTT as a busy placement */
	abo->placement.num_busy_placement = 1;
	abo->placement.busy_placement = &abo->placements[1];

	r = ttm_bo_validate(bo, &abo->placement, &ctx);
	if (unlikely(r != 0))
		return r;

	offset = bo->mem.start << PAGE_SHIFT;
	/* this should never happen */
	if (bo->mem.mem_type == TTM_PL_VRAM &&
	    (offset + size) > adev->gmc.visible_vram_size)
		return -EINVAL;

	return 0;
}