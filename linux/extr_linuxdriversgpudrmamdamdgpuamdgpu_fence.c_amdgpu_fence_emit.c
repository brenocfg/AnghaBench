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
typedef  size_t uint32_t ;
struct dma_fence {int dummy; } ;
struct TYPE_2__ {size_t sync_seq; size_t num_fences_mask; struct dma_fence** fences; int /*<<< orphan*/  gpu_addr; int /*<<< orphan*/  lock; } ;
struct amdgpu_ring {TYPE_1__ fence_drv; scalar_t__ idx; struct amdgpu_device* adev; } ;
struct amdgpu_fence {struct dma_fence base; struct amdgpu_ring* ring; } ;
struct amdgpu_device {scalar_t__ fence_context; } ;

/* Variables and functions */
 unsigned int AMDGPU_FENCE_FLAG_INT ; 
 int /*<<< orphan*/  DRM_INFO (char*) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  amdgpu_fence_ops ; 
 int /*<<< orphan*/  amdgpu_fence_slab ; 
 int /*<<< orphan*/  amdgpu_ring_emit_fence (struct amdgpu_ring*,int /*<<< orphan*/ ,size_t,unsigned int) ; 
 int /*<<< orphan*/  dma_fence_get (struct dma_fence*) ; 
 int /*<<< orphan*/  dma_fence_init (struct dma_fence*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__,size_t) ; 
 int /*<<< orphan*/  dma_fence_is_signaled (struct dma_fence*) ; 
 int /*<<< orphan*/  dma_fence_wait (struct dma_fence*,int) ; 
 struct amdgpu_fence* kmem_cache_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_assign_pointer (struct dma_fence*,int /*<<< orphan*/ ) ; 
 struct dma_fence* rcu_dereference_protected (struct dma_fence*,int) ; 

int amdgpu_fence_emit(struct amdgpu_ring *ring, struct dma_fence **f,
		      unsigned flags)
{
	struct amdgpu_device *adev = ring->adev;
	struct amdgpu_fence *fence;
	struct dma_fence *old, **ptr;
	uint32_t seq;

	fence = kmem_cache_alloc(amdgpu_fence_slab, GFP_KERNEL);
	if (fence == NULL)
		return -ENOMEM;

	seq = ++ring->fence_drv.sync_seq;
	fence->ring = ring;
	dma_fence_init(&fence->base, &amdgpu_fence_ops,
		       &ring->fence_drv.lock,
		       adev->fence_context + ring->idx,
		       seq);
	amdgpu_ring_emit_fence(ring, ring->fence_drv.gpu_addr,
			       seq, flags | AMDGPU_FENCE_FLAG_INT);

	ptr = &ring->fence_drv.fences[seq & ring->fence_drv.num_fences_mask];
	/* This function can't be called concurrently anyway, otherwise
	 * emitting the fence would mess up the hardware ring buffer.
	 */
	old = rcu_dereference_protected(*ptr, 1);
	if (old && !dma_fence_is_signaled(old)) {
		DRM_INFO("rcu slot is busy\n");
		dma_fence_wait(old, false);
	}

	rcu_assign_pointer(*ptr, dma_fence_get(&fence->base));

	*f = &fence->base;

	return 0;
}