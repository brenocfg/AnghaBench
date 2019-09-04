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
typedef  int uint64_t ;
struct dma_fence {int dummy; } ;
struct amdgpu_ring {size_t idx; } ;
struct amdgpu_ctx_ring {int sequence; struct dma_fence** fences; } ;
struct amdgpu_ctx {int /*<<< orphan*/  ring_lock; struct amdgpu_ctx_ring* rings; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int amdgpu_sched_jobs ; 
 int /*<<< orphan*/  dma_fence_get (struct dma_fence*) ; 
 int /*<<< orphan*/  dma_fence_is_signaled (struct dma_fence*) ; 
 int /*<<< orphan*/  dma_fence_put (struct dma_fence*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

int amdgpu_ctx_add_fence(struct amdgpu_ctx *ctx, struct amdgpu_ring *ring,
			      struct dma_fence *fence, uint64_t* handler)
{
	struct amdgpu_ctx_ring *cring = & ctx->rings[ring->idx];
	uint64_t seq = cring->sequence;
	unsigned idx = 0;
	struct dma_fence *other = NULL;

	idx = seq & (amdgpu_sched_jobs - 1);
	other = cring->fences[idx];
	if (other)
		BUG_ON(!dma_fence_is_signaled(other));

	dma_fence_get(fence);

	spin_lock(&ctx->ring_lock);
	cring->fences[idx] = fence;
	cring->sequence++;
	spin_unlock(&ctx->ring_lock);

	dma_fence_put(other);
	if (handler)
		*handler = seq;

	return 0;
}