#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct ttm_mem_reg {int num_pages; scalar_t__ mem_type; } ;
struct TYPE_4__ {int /*<<< orphan*/  resv; } ;
struct ttm_buffer_object {scalar_t__ type; TYPE_1__ base; int /*<<< orphan*/  bdev; } ;
struct dma_fence {int dummy; } ;
struct amdgpu_device {int dummy; } ;
struct amdgpu_copy_mem {scalar_t__ offset; struct ttm_mem_reg* mem; struct ttm_buffer_object* bo; } ;
struct TYPE_5__ {int flags; } ;

/* Variables and functions */
 int AMDGPU_GEM_CREATE_VRAM_WIPE_ON_RELEASE ; 
 int /*<<< orphan*/  AMDGPU_POISON ; 
 int PAGE_SHIFT ; 
 scalar_t__ TTM_PL_VRAM ; 
 int amdgpu_fill_buffer (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct dma_fence**) ; 
 struct amdgpu_device* amdgpu_ttm_adev (int /*<<< orphan*/ ) ; 
 int amdgpu_ttm_copy_mem_to_mem (struct amdgpu_device*,struct amdgpu_copy_mem*,struct amdgpu_copy_mem*,int,int /*<<< orphan*/ ,struct dma_fence**) ; 
 int /*<<< orphan*/  dma_fence_put (struct dma_fence*) ; 
 int /*<<< orphan*/  dma_fence_wait (struct dma_fence*,int) ; 
 int ttm_bo_move_accel_cleanup (struct ttm_buffer_object*,struct dma_fence*,int,struct ttm_mem_reg*) ; 
 int ttm_bo_pipeline_move (struct ttm_buffer_object*,struct dma_fence*,int,struct ttm_mem_reg*) ; 
 scalar_t__ ttm_bo_type_kernel ; 
 TYPE_2__* ttm_to_amdgpu_bo (struct ttm_buffer_object*) ; 

__attribute__((used)) static int amdgpu_move_blit(struct ttm_buffer_object *bo,
			    bool evict, bool no_wait_gpu,
			    struct ttm_mem_reg *new_mem,
			    struct ttm_mem_reg *old_mem)
{
	struct amdgpu_device *adev = amdgpu_ttm_adev(bo->bdev);
	struct amdgpu_copy_mem src, dst;
	struct dma_fence *fence = NULL;
	int r;

	src.bo = bo;
	dst.bo = bo;
	src.mem = old_mem;
	dst.mem = new_mem;
	src.offset = 0;
	dst.offset = 0;

	r = amdgpu_ttm_copy_mem_to_mem(adev, &src, &dst,
				       new_mem->num_pages << PAGE_SHIFT,
				       bo->base.resv, &fence);
	if (r)
		goto error;

	/* clear the space being freed */
	if (old_mem->mem_type == TTM_PL_VRAM &&
	    (ttm_to_amdgpu_bo(bo)->flags &
	     AMDGPU_GEM_CREATE_VRAM_WIPE_ON_RELEASE)) {
		struct dma_fence *wipe_fence = NULL;

		r = amdgpu_fill_buffer(ttm_to_amdgpu_bo(bo), AMDGPU_POISON,
				       NULL, &wipe_fence);
		if (r) {
			goto error;
		} else if (wipe_fence) {
			dma_fence_put(fence);
			fence = wipe_fence;
		}
	}

	/* Always block for VM page tables before committing the new location */
	if (bo->type == ttm_bo_type_kernel)
		r = ttm_bo_move_accel_cleanup(bo, fence, true, new_mem);
	else
		r = ttm_bo_pipeline_move(bo, fence, evict, new_mem);
	dma_fence_put(fence);
	return r;

error:
	if (fence)
		dma_fence_wait(fence, false);
	dma_fence_put(fence);
	return r;
}