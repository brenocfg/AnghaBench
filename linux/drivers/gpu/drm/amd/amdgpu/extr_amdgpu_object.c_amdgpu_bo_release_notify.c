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
struct TYPE_4__ {int /*<<< orphan*/  resv; } ;
struct TYPE_3__ {scalar_t__ mem_type; int /*<<< orphan*/  mm_node; } ;
struct ttm_buffer_object {TYPE_2__ base; TYPE_1__ mem; } ;
struct dma_fence {int dummy; } ;
struct amdgpu_bo {int flags; scalar_t__ kfd_bo; } ;

/* Variables and functions */
 int AMDGPU_GEM_CREATE_VRAM_WIPE_ON_RELEASE ; 
 int /*<<< orphan*/  AMDGPU_POISON ; 
 scalar_t__ TTM_PL_VRAM ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  amdgpu_amdkfd_unreserve_memory_limit (struct amdgpu_bo*) ; 
 int /*<<< orphan*/  amdgpu_bo_fence (struct amdgpu_bo*,struct dma_fence*,int) ; 
 int /*<<< orphan*/  amdgpu_bo_is_amdgpu_bo (struct ttm_buffer_object*) ; 
 int amdgpu_fill_buffer (struct amdgpu_bo*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct dma_fence**) ; 
 int /*<<< orphan*/  dma_fence_put (struct dma_fence*) ; 
 int /*<<< orphan*/  dma_resv_lock (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dma_resv_unlock (int /*<<< orphan*/ ) ; 
 struct amdgpu_bo* ttm_to_amdgpu_bo (struct ttm_buffer_object*) ; 

void amdgpu_bo_release_notify(struct ttm_buffer_object *bo)
{
	struct dma_fence *fence = NULL;
	struct amdgpu_bo *abo;
	int r;

	if (!amdgpu_bo_is_amdgpu_bo(bo))
		return;

	abo = ttm_to_amdgpu_bo(bo);

	if (abo->kfd_bo)
		amdgpu_amdkfd_unreserve_memory_limit(abo);

	if (bo->mem.mem_type != TTM_PL_VRAM || !bo->mem.mm_node ||
	    !(abo->flags & AMDGPU_GEM_CREATE_VRAM_WIPE_ON_RELEASE))
		return;

	dma_resv_lock(bo->base.resv, NULL);

	r = amdgpu_fill_buffer(abo, AMDGPU_POISON, bo->base.resv, &fence);
	if (!WARN_ON(r)) {
		amdgpu_bo_fence(abo, fence, false);
		dma_fence_put(fence);
	}

	dma_resv_unlock(bo->base.resv);
}