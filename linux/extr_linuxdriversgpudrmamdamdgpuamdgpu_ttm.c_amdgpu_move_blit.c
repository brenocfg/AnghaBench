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
struct ttm_mem_reg {int num_pages; } ;
struct ttm_buffer_object {int /*<<< orphan*/  resv; int /*<<< orphan*/  bdev; } ;
struct dma_fence {int dummy; } ;
struct amdgpu_device {int dummy; } ;
struct amdgpu_copy_mem {scalar_t__ offset; struct ttm_mem_reg* mem; struct ttm_buffer_object* bo; } ;

/* Variables and functions */
 int PAGE_SHIFT ; 
 struct amdgpu_device* amdgpu_ttm_adev (int /*<<< orphan*/ ) ; 
 int amdgpu_ttm_copy_mem_to_mem (struct amdgpu_device*,struct amdgpu_copy_mem*,struct amdgpu_copy_mem*,int,int /*<<< orphan*/ ,struct dma_fence**) ; 
 int /*<<< orphan*/  dma_fence_put (struct dma_fence*) ; 
 int /*<<< orphan*/  dma_fence_wait (struct dma_fence*,int) ; 
 int ttm_bo_pipeline_move (struct ttm_buffer_object*,struct dma_fence*,int,struct ttm_mem_reg*) ; 

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
				       bo->resv, &fence);
	if (r)
		goto error;

	r = ttm_bo_pipeline_move(bo, fence, evict, new_mem);
	dma_fence_put(fence);
	return r;

error:
	if (fence)
		dma_fence_wait(fence, false);
	dma_fence_put(fence);
	return r;
}