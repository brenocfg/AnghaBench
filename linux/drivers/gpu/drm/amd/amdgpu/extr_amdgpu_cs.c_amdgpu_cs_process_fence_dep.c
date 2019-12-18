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
struct drm_sched_fence {int /*<<< orphan*/  scheduled; } ;
struct drm_sched_entity {int dummy; } ;
struct drm_amdgpu_cs_chunk_dep {int /*<<< orphan*/  handle; int /*<<< orphan*/  ring; int /*<<< orphan*/  ip_instance; int /*<<< orphan*/  ip_type; int /*<<< orphan*/  ctx_id; } ;
struct dma_fence {int dummy; } ;
struct amdgpu_fpriv {int dummy; } ;
struct amdgpu_ctx {int dummy; } ;
struct amdgpu_cs_parser {TYPE_2__* job; int /*<<< orphan*/  adev; TYPE_1__* filp; } ;
struct amdgpu_cs_chunk {int length_dw; scalar_t__ chunk_id; scalar_t__ kdata; } ;
struct TYPE_4__ {int /*<<< orphan*/  sync; } ;
struct TYPE_3__ {struct amdgpu_fpriv* driver_priv; } ;

/* Variables and functions */
 scalar_t__ AMDGPU_CHUNK_ID_SCHEDULED_DEPENDENCIES ; 
 int EINVAL ; 
 scalar_t__ IS_ERR (struct dma_fence*) ; 
 int PTR_ERR (struct dma_fence*) ; 
 struct amdgpu_ctx* amdgpu_ctx_get (struct amdgpu_fpriv*,int /*<<< orphan*/ ) ; 
 int amdgpu_ctx_get_entity (struct amdgpu_ctx*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct drm_sched_entity**) ; 
 struct dma_fence* amdgpu_ctx_get_fence (struct amdgpu_ctx*,struct drm_sched_entity*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  amdgpu_ctx_put (struct amdgpu_ctx*) ; 
 int amdgpu_sync_fence (int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct dma_fence*,int) ; 
 struct dma_fence* dma_fence_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dma_fence_put (struct dma_fence*) ; 
 struct drm_sched_fence* to_drm_sched_fence (struct dma_fence*) ; 

__attribute__((used)) static int amdgpu_cs_process_fence_dep(struct amdgpu_cs_parser *p,
				       struct amdgpu_cs_chunk *chunk)
{
	struct amdgpu_fpriv *fpriv = p->filp->driver_priv;
	unsigned num_deps;
	int i, r;
	struct drm_amdgpu_cs_chunk_dep *deps;

	deps = (struct drm_amdgpu_cs_chunk_dep *)chunk->kdata;
	num_deps = chunk->length_dw * 4 /
		sizeof(struct drm_amdgpu_cs_chunk_dep);

	for (i = 0; i < num_deps; ++i) {
		struct amdgpu_ctx *ctx;
		struct drm_sched_entity *entity;
		struct dma_fence *fence;

		ctx = amdgpu_ctx_get(fpriv, deps[i].ctx_id);
		if (ctx == NULL)
			return -EINVAL;

		r = amdgpu_ctx_get_entity(ctx, deps[i].ip_type,
					  deps[i].ip_instance,
					  deps[i].ring, &entity);
		if (r) {
			amdgpu_ctx_put(ctx);
			return r;
		}

		fence = amdgpu_ctx_get_fence(ctx, entity, deps[i].handle);
		amdgpu_ctx_put(ctx);

		if (IS_ERR(fence))
			return PTR_ERR(fence);
		else if (!fence)
			continue;

		if (chunk->chunk_id == AMDGPU_CHUNK_ID_SCHEDULED_DEPENDENCIES) {
			struct drm_sched_fence *s_fence;
			struct dma_fence *old = fence;

			s_fence = to_drm_sched_fence(fence);
			fence = dma_fence_get(&s_fence->scheduled);
			dma_fence_put(old);
		}

		r = amdgpu_sync_fence(p->adev, &p->job->sync, fence, true);
		dma_fence_put(fence);
		if (r)
			return r;
	}
	return 0;
}