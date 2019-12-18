#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint64_t ;
struct msm_gem_submit {int valid; int nr_bos; TYPE_1__* bos; int /*<<< orphan*/  aspace; } ;
struct msm_gem_object {int /*<<< orphan*/  base; } ;
struct TYPE_2__ {scalar_t__ iova; int /*<<< orphan*/  flags; struct msm_gem_object* obj; } ;

/* Variables and functions */
 int /*<<< orphan*/  BO_PINNED ; 
 int /*<<< orphan*/  BO_VALID ; 
 int msm_gem_get_and_pin_iova (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__*) ; 

__attribute__((used)) static int submit_pin_objects(struct msm_gem_submit *submit)
{
	int i, ret = 0;

	submit->valid = true;

	for (i = 0; i < submit->nr_bos; i++) {
		struct msm_gem_object *msm_obj = submit->bos[i].obj;
		uint64_t iova;

		/* if locking succeeded, pin bo: */
		ret = msm_gem_get_and_pin_iova(&msm_obj->base,
				submit->aspace, &iova);

		if (ret)
			break;

		submit->bos[i].flags |= BO_PINNED;

		if (iova == submit->bos[i].iova) {
			submit->bos[i].flags |= BO_VALID;
		} else {
			submit->bos[i].iova = iova;
			/* iova changed, so address in cmdstream is not valid: */
			submit->bos[i].flags &= ~BO_VALID;
			submit->valid = false;
		}
	}

	return ret;
}