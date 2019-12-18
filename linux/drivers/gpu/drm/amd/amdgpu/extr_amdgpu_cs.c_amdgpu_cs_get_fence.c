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
struct drm_file {int /*<<< orphan*/  driver_priv; } ;
struct drm_amdgpu_fence {int /*<<< orphan*/  seq_no; int /*<<< orphan*/  ring; int /*<<< orphan*/  ip_instance; int /*<<< orphan*/  ip_type; int /*<<< orphan*/  ctx_id; } ;
struct dma_fence {int dummy; } ;
struct amdgpu_device {int dummy; } ;
struct amdgpu_ctx {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 struct dma_fence* ERR_PTR (int) ; 
 struct amdgpu_ctx* amdgpu_ctx_get (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int amdgpu_ctx_get_entity (struct amdgpu_ctx*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct drm_sched_entity**) ; 
 struct dma_fence* amdgpu_ctx_get_fence (struct amdgpu_ctx*,struct drm_sched_entity*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  amdgpu_ctx_put (struct amdgpu_ctx*) ; 

__attribute__((used)) static struct dma_fence *amdgpu_cs_get_fence(struct amdgpu_device *adev,
					     struct drm_file *filp,
					     struct drm_amdgpu_fence *user)
{
	struct drm_sched_entity *entity;
	struct amdgpu_ctx *ctx;
	struct dma_fence *fence;
	int r;

	ctx = amdgpu_ctx_get(filp->driver_priv, user->ctx_id);
	if (ctx == NULL)
		return ERR_PTR(-EINVAL);

	r = amdgpu_ctx_get_entity(ctx, user->ip_type, user->ip_instance,
				  user->ring, &entity);
	if (r) {
		amdgpu_ctx_put(ctx);
		return ERR_PTR(r);
	}

	fence = amdgpu_ctx_get_fence(ctx, entity, user->seq_no);
	amdgpu_ctx_put(ctx);

	return fence;
}