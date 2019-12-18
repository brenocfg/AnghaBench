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
struct drm_sched_entity {int dummy; } ;
struct dma_fence {int dummy; } ;
struct amdgpu_ctx_entity {int sequence; int /*<<< orphan*/ * fences; } ;
struct amdgpu_ctx {int /*<<< orphan*/  ring_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_ERROR (char*,long) ; 
 long ERESTARTSYS ; 
 int amdgpu_sched_jobs ; 
 struct dma_fence* dma_fence_get (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_fence_put (struct dma_fence*) ; 
 long dma_fence_wait (struct dma_fence*,int) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 struct amdgpu_ctx_entity* to_amdgpu_ctx_entity (struct drm_sched_entity*) ; 

int amdgpu_ctx_wait_prev_fence(struct amdgpu_ctx *ctx,
			       struct drm_sched_entity *entity)
{
	struct amdgpu_ctx_entity *centity = to_amdgpu_ctx_entity(entity);
	struct dma_fence *other;
	unsigned idx;
	long r;

	spin_lock(&ctx->ring_lock);
	idx = centity->sequence & (amdgpu_sched_jobs - 1);
	other = dma_fence_get(centity->fences[idx]);
	spin_unlock(&ctx->ring_lock);

	if (!other)
		return 0;

	r = dma_fence_wait(other, true);
	if (r < 0 && r != -ERESTARTSYS)
		DRM_ERROR("Error (%ld) waiting for fence!\n", r);

	dma_fence_put(other);
	return r;
}