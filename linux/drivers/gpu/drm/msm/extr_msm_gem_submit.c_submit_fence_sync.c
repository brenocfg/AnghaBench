#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct msm_gem_submit {int nr_bos; TYPE_1__* ring; TYPE_2__* bos; } ;
struct TYPE_6__ {int /*<<< orphan*/  resv; } ;
struct msm_gem_object {TYPE_3__ base; } ;
struct TYPE_5__ {int flags; struct msm_gem_object* obj; } ;
struct TYPE_4__ {int /*<<< orphan*/  fctx; } ;

/* Variables and functions */
 int MSM_SUBMIT_BO_WRITE ; 
 int dma_resv_reserve_shared (int /*<<< orphan*/ ,int) ; 
 int msm_gem_sync_object (TYPE_3__*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int submit_fence_sync(struct msm_gem_submit *submit, bool no_implicit)
{
	int i, ret = 0;

	for (i = 0; i < submit->nr_bos; i++) {
		struct msm_gem_object *msm_obj = submit->bos[i].obj;
		bool write = submit->bos[i].flags & MSM_SUBMIT_BO_WRITE;

		if (!write) {
			/* NOTE: _reserve_shared() must happen before
			 * _add_shared_fence(), which makes this a slightly
			 * strange place to call it.  OTOH this is a
			 * convenient can-fail point to hook it in.
			 */
			ret = dma_resv_reserve_shared(msm_obj->base.resv,
								1);
			if (ret)
				return ret;
		}

		if (no_implicit)
			continue;

		ret = msm_gem_sync_object(&msm_obj->base, submit->ring->fctx,
			write);
		if (ret)
			break;
	}

	return ret;
}