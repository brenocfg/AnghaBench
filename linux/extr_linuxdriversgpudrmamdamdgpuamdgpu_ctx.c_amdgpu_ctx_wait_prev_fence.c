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
struct dma_fence {int dummy; } ;
struct amdgpu_ctx_ring {int sequence; struct dma_fence** fences; } ;
struct amdgpu_ctx {struct amdgpu_ctx_ring* rings; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_ERROR (char*,long) ; 
 long ERESTARTSYS ; 
 int amdgpu_sched_jobs ; 
 long dma_fence_wait (struct dma_fence*,int) ; 

int amdgpu_ctx_wait_prev_fence(struct amdgpu_ctx *ctx, unsigned ring_id)
{
	struct amdgpu_ctx_ring *cring = &ctx->rings[ring_id];
	unsigned idx = cring->sequence & (amdgpu_sched_jobs - 1);
	struct dma_fence *other = cring->fences[idx];

	if (other) {
		signed long r;
		r = dma_fence_wait(other, true);
		if (r < 0) {
			if (r != -ERESTARTSYS)
				DRM_ERROR("Error (%ld) waiting for fence!\n", r);

			return r;
		}
	}

	return 0;
}