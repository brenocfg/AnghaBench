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
struct drm_amdgpu_cs_chunk_dep {int /*<<< orphan*/  handle; int /*<<< orphan*/  ring; int /*<<< orphan*/  ip_instance; int /*<<< orphan*/  ip_type; int /*<<< orphan*/  ctx_id; } ;
struct dma_fence {int dummy; } ;
struct amdgpu_ring {int dummy; } ;
struct amdgpu_fpriv {int dummy; } ;
struct amdgpu_ctx {int /*<<< orphan*/  queue_mgr; } ;
struct amdgpu_cs_parser {TYPE_2__* job; int /*<<< orphan*/  adev; TYPE_1__* filp; } ;
struct amdgpu_cs_chunk {int length_dw; scalar_t__ kdata; } ;
struct TYPE_4__ {int /*<<< orphan*/  sync; } ;
struct TYPE_3__ {struct amdgpu_fpriv* driver_priv; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ IS_ERR (struct dma_fence*) ; 
 int PTR_ERR (struct dma_fence*) ; 
 struct amdgpu_ctx* amdgpu_ctx_get (struct amdgpu_fpriv*,int /*<<< orphan*/ ) ; 
 struct dma_fence* amdgpu_ctx_get_fence (struct amdgpu_ctx*,struct amdgpu_ring*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  amdgpu_ctx_put (struct amdgpu_ctx*) ; 
 int amdgpu_queue_mgr_map (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct amdgpu_ring**) ; 
 int amdgpu_sync_fence (int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct dma_fence*,int) ; 
 int /*<<< orphan*/  dma_fence_put (struct dma_fence*) ; 

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
		struct amdgpu_ring *ring;
		struct amdgpu_ctx *ctx;
		struct dma_fence *fence;

		ctx = amdgpu_ctx_get(fpriv, deps[i].ctx_id);
		if (ctx == NULL)
			return -EINVAL;

		r = amdgpu_queue_mgr_map(p->adev, &ctx->queue_mgr,
					 deps[i].ip_type,
					 deps[i].ip_instance,
					 deps[i].ring, &ring);
		if (r) {
			amdgpu_ctx_put(ctx);
			return r;
		}

		fence = amdgpu_ctx_get_fence(ctx, ring,
					     deps[i].handle);
		if (IS_ERR(fence)) {
			r = PTR_ERR(fence);
			amdgpu_ctx_put(ctx);
			return r;
		} else if (fence) {
			r = amdgpu_sync_fence(p->adev, &p->job->sync, fence,
					true);
			dma_fence_put(fence);
			amdgpu_ctx_put(ctx);
			if (r)
				return r;
		}
	}
	return 0;
}