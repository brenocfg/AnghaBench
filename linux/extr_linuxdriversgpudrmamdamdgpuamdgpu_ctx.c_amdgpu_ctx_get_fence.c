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
typedef  unsigned long long uint64_t ;
struct dma_fence {int dummy; } ;
struct amdgpu_ring {size_t idx; } ;
struct amdgpu_ctx_ring {int sequence; int /*<<< orphan*/ * fences; } ;
struct amdgpu_ctx {int /*<<< orphan*/  ring_lock; struct amdgpu_ctx_ring* rings; } ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 struct dma_fence* ERR_PTR (int /*<<< orphan*/ ) ; 
 unsigned long long amdgpu_sched_jobs ; 
 struct dma_fence* dma_fence_get (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

struct dma_fence *amdgpu_ctx_get_fence(struct amdgpu_ctx *ctx,
				       struct amdgpu_ring *ring, uint64_t seq)
{
	struct amdgpu_ctx_ring *cring = & ctx->rings[ring->idx];
	struct dma_fence *fence;

	spin_lock(&ctx->ring_lock);

	if (seq == ~0ull)
		seq = ctx->rings[ring->idx].sequence - 1;

	if (seq >= cring->sequence) {
		spin_unlock(&ctx->ring_lock);
		return ERR_PTR(-EINVAL);
	}


	if (seq + amdgpu_sched_jobs < cring->sequence) {
		spin_unlock(&ctx->ring_lock);
		return NULL;
	}

	fence = dma_fence_get(cring->fences[seq & (amdgpu_sched_jobs - 1)]);
	spin_unlock(&ctx->ring_lock);

	return fence;
}