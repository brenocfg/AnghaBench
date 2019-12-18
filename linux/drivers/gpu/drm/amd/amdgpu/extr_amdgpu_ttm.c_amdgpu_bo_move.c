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
typedef  int u64 ;
struct ttm_operation_ctx {int /*<<< orphan*/  no_wait_gpu; } ;
struct ttm_mem_reg {scalar_t__ mem_type; } ;
struct ttm_buffer_object {scalar_t__ type; scalar_t__ num_pages; int /*<<< orphan*/ * ttm; int /*<<< orphan*/  bdev; struct ttm_mem_reg mem; } ;
struct TYPE_2__ {int /*<<< orphan*/  buffer_funcs_enabled; } ;
struct amdgpu_device {int /*<<< orphan*/  num_bytes_moved; TYPE_1__ mman; } ;
struct amdgpu_bo {scalar_t__ pin_count; int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  AMDGPU_GEM_CREATE_CPU_ACCESS_REQUIRED ; 
 scalar_t__ AMDGPU_PL_GDS ; 
 scalar_t__ AMDGPU_PL_GWS ; 
 scalar_t__ AMDGPU_PL_OA ; 
 int EINVAL ; 
 int ENODEV ; 
 int PAGE_SHIFT ; 
 scalar_t__ TTM_PL_SYSTEM ; 
 scalar_t__ TTM_PL_TT ; 
 scalar_t__ TTM_PL_VRAM ; 
 scalar_t__ WARN_ON_ONCE (int) ; 
 int /*<<< orphan*/  amdgpu_mem_visible (struct amdgpu_device*,struct ttm_mem_reg*) ; 
 int amdgpu_move_blit (struct ttm_buffer_object*,int,int /*<<< orphan*/ ,struct ttm_mem_reg*,struct ttm_mem_reg*) ; 
 int /*<<< orphan*/  amdgpu_move_null (struct ttm_buffer_object*,struct ttm_mem_reg*) ; 
 int amdgpu_move_ram_vram (struct ttm_buffer_object*,int,struct ttm_operation_ctx*,struct ttm_mem_reg*) ; 
 int amdgpu_move_vram_ram (struct ttm_buffer_object*,int,struct ttm_operation_ctx*,struct ttm_mem_reg*) ; 
 struct amdgpu_device* amdgpu_ttm_adev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atomic64_add (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int ttm_bo_move_memcpy (struct ttm_buffer_object*,struct ttm_operation_ctx*,struct ttm_mem_reg*) ; 
 scalar_t__ ttm_bo_type_device ; 
 struct amdgpu_bo* ttm_to_amdgpu_bo (struct ttm_buffer_object*) ; 

__attribute__((used)) static int amdgpu_bo_move(struct ttm_buffer_object *bo, bool evict,
			  struct ttm_operation_ctx *ctx,
			  struct ttm_mem_reg *new_mem)
{
	struct amdgpu_device *adev;
	struct amdgpu_bo *abo;
	struct ttm_mem_reg *old_mem = &bo->mem;
	int r;

	/* Can't move a pinned BO */
	abo = ttm_to_amdgpu_bo(bo);
	if (WARN_ON_ONCE(abo->pin_count > 0))
		return -EINVAL;

	adev = amdgpu_ttm_adev(bo->bdev);

	if (old_mem->mem_type == TTM_PL_SYSTEM && bo->ttm == NULL) {
		amdgpu_move_null(bo, new_mem);
		return 0;
	}
	if ((old_mem->mem_type == TTM_PL_TT &&
	     new_mem->mem_type == TTM_PL_SYSTEM) ||
	    (old_mem->mem_type == TTM_PL_SYSTEM &&
	     new_mem->mem_type == TTM_PL_TT)) {
		/* bind is enough */
		amdgpu_move_null(bo, new_mem);
		return 0;
	}
	if (old_mem->mem_type == AMDGPU_PL_GDS ||
	    old_mem->mem_type == AMDGPU_PL_GWS ||
	    old_mem->mem_type == AMDGPU_PL_OA ||
	    new_mem->mem_type == AMDGPU_PL_GDS ||
	    new_mem->mem_type == AMDGPU_PL_GWS ||
	    new_mem->mem_type == AMDGPU_PL_OA) {
		/* Nothing to save here */
		amdgpu_move_null(bo, new_mem);
		return 0;
	}

	if (!adev->mman.buffer_funcs_enabled) {
		r = -ENODEV;
		goto memcpy;
	}

	if (old_mem->mem_type == TTM_PL_VRAM &&
	    new_mem->mem_type == TTM_PL_SYSTEM) {
		r = amdgpu_move_vram_ram(bo, evict, ctx, new_mem);
	} else if (old_mem->mem_type == TTM_PL_SYSTEM &&
		   new_mem->mem_type == TTM_PL_VRAM) {
		r = amdgpu_move_ram_vram(bo, evict, ctx, new_mem);
	} else {
		r = amdgpu_move_blit(bo, evict, ctx->no_wait_gpu,
				     new_mem, old_mem);
	}

	if (r) {
memcpy:
		/* Check that all memory is CPU accessible */
		if (!amdgpu_mem_visible(adev, old_mem) ||
		    !amdgpu_mem_visible(adev, new_mem)) {
			pr_err("Move buffer fallback to memcpy unavailable\n");
			return r;
		}

		r = ttm_bo_move_memcpy(bo, ctx, new_mem);
		if (r)
			return r;
	}

	if (bo->type == ttm_bo_type_device &&
	    new_mem->mem_type == TTM_PL_VRAM &&
	    old_mem->mem_type != TTM_PL_VRAM) {
		/* amdgpu_bo_fault_reserve_notify will re-set this if the CPU
		 * accesses the BO after it's moved.
		 */
		abo->flags &= ~AMDGPU_GEM_CREATE_CPU_ACCESS_REQUIRED;
	}

	/* update statistics */
	atomic64_add((u64)bo->num_pages << PAGE_SHIFT, &adev->num_bytes_moved);
	return 0;
}