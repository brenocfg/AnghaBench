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
struct msm_fence_context {scalar_t__ context; } ;
struct drm_gem_object {int /*<<< orphan*/  resv; } ;
struct dma_resv_list {int shared_count; int /*<<< orphan*/ * shared; } ;
struct dma_fence {scalar_t__ context; } ;

/* Variables and functions */
 int dma_fence_wait (struct dma_fence*,int) ; 
 struct dma_fence* dma_resv_get_excl (int /*<<< orphan*/ ) ; 
 struct dma_resv_list* dma_resv_get_list (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_resv_held (int /*<<< orphan*/ ) ; 
 struct dma_fence* rcu_dereference_protected (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int msm_gem_sync_object(struct drm_gem_object *obj,
		struct msm_fence_context *fctx, bool exclusive)
{
	struct dma_resv_list *fobj;
	struct dma_fence *fence;
	int i, ret;

	fobj = dma_resv_get_list(obj->resv);
	if (!fobj || (fobj->shared_count == 0)) {
		fence = dma_resv_get_excl(obj->resv);
		/* don't need to wait on our own fences, since ring is fifo */
		if (fence && (fence->context != fctx->context)) {
			ret = dma_fence_wait(fence, true);
			if (ret)
				return ret;
		}
	}

	if (!exclusive || !fobj)
		return 0;

	for (i = 0; i < fobj->shared_count; i++) {
		fence = rcu_dereference_protected(fobj->shared[i],
						dma_resv_held(obj->resv));
		if (fence->context != fctx->context) {
			ret = dma_fence_wait(fence, true);
			if (ret)
				return ret;
		}
	}

	return 0;
}