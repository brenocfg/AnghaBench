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
struct TYPE_4__ {int status; } ;
struct TYPE_3__ {int /*<<< orphan*/  handle; int /*<<< orphan*/  ring; int /*<<< orphan*/  ip_instance; int /*<<< orphan*/  ip_type; int /*<<< orphan*/  ctx_id; int /*<<< orphan*/  timeout; } ;
union drm_amdgpu_wait_cs {TYPE_2__ out; TYPE_1__ in; } ;
struct drm_sched_entity {int dummy; } ;
struct drm_file {int /*<<< orphan*/  driver_priv; } ;
struct drm_device {int dummy; } ;
struct dma_fence {long error; } ;
struct amdgpu_ctx {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ IS_ERR (struct dma_fence*) ; 
 long PTR_ERR (struct dma_fence*) ; 
 struct amdgpu_ctx* amdgpu_ctx_get (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 long amdgpu_ctx_get_entity (struct amdgpu_ctx*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct drm_sched_entity**) ; 
 struct dma_fence* amdgpu_ctx_get_fence (struct amdgpu_ctx*,struct drm_sched_entity*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  amdgpu_ctx_put (struct amdgpu_ctx*) ; 
 unsigned long amdgpu_gem_timeout (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_fence_put (struct dma_fence*) ; 
 long dma_fence_wait_timeout (struct dma_fence*,int,unsigned long) ; 
 int /*<<< orphan*/  memset (union drm_amdgpu_wait_cs*,int /*<<< orphan*/ ,int) ; 

int amdgpu_cs_wait_ioctl(struct drm_device *dev, void *data,
			 struct drm_file *filp)
{
	union drm_amdgpu_wait_cs *wait = data;
	unsigned long timeout = amdgpu_gem_timeout(wait->in.timeout);
	struct drm_sched_entity *entity;
	struct amdgpu_ctx *ctx;
	struct dma_fence *fence;
	long r;

	ctx = amdgpu_ctx_get(filp->driver_priv, wait->in.ctx_id);
	if (ctx == NULL)
		return -EINVAL;

	r = amdgpu_ctx_get_entity(ctx, wait->in.ip_type, wait->in.ip_instance,
				  wait->in.ring, &entity);
	if (r) {
		amdgpu_ctx_put(ctx);
		return r;
	}

	fence = amdgpu_ctx_get_fence(ctx, entity, wait->in.handle);
	if (IS_ERR(fence))
		r = PTR_ERR(fence);
	else if (fence) {
		r = dma_fence_wait_timeout(fence, true, timeout);
		if (r > 0 && fence->error)
			r = fence->error;
		dma_fence_put(fence);
	} else
		r = 1;

	amdgpu_ctx_put(ctx);
	if (r < 0)
		return r;

	memset(wait, 0, sizeof(*wait));
	wait->out.status = (r == 0);

	return 0;
}