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
struct reservation_object_list {int shared_count; int /*<<< orphan*/ * shared; } ;
struct msm_gem_object {int /*<<< orphan*/  resv; } ;
struct msm_fence_context {scalar_t__ context; } ;
struct drm_gem_object {int dummy; } ;
struct dma_fence {scalar_t__ context; } ;

/* Variables and functions */
 int dma_fence_wait (struct dma_fence*,int) ; 
 struct dma_fence* rcu_dereference_protected (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct dma_fence* reservation_object_get_excl (int /*<<< orphan*/ ) ; 
 struct reservation_object_list* reservation_object_get_list (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reservation_object_held (int /*<<< orphan*/ ) ; 
 struct msm_gem_object* to_msm_bo (struct drm_gem_object*) ; 

int msm_gem_sync_object(struct drm_gem_object *obj,
		struct msm_fence_context *fctx, bool exclusive)
{
	struct msm_gem_object *msm_obj = to_msm_bo(obj);
	struct reservation_object_list *fobj;
	struct dma_fence *fence;
	int i, ret;

	fobj = reservation_object_get_list(msm_obj->resv);
	if (!fobj || (fobj->shared_count == 0)) {
		fence = reservation_object_get_excl(msm_obj->resv);
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
						reservation_object_held(msm_obj->resv));
		if (fence->context != fctx->context) {
			ret = dma_fence_wait(fence, true);
			if (ret)
				return ret;
		}
	}

	return 0;
}