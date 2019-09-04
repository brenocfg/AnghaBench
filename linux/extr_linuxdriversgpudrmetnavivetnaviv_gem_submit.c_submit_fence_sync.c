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
struct reservation_object {int dummy; } ;
struct etnaviv_gem_submit_bo {int flags; int /*<<< orphan*/  excl; int /*<<< orphan*/  shared; int /*<<< orphan*/  nr_shared; TYPE_1__* obj; } ;
struct etnaviv_gem_submit {int nr_bos; int flags; struct etnaviv_gem_submit_bo* bos; } ;
struct TYPE_2__ {struct reservation_object* resv; } ;

/* Variables and functions */
 int ETNA_SUBMIT_BO_WRITE ; 
 int ETNA_SUBMIT_NO_IMPLICIT ; 
 int /*<<< orphan*/  reservation_object_get_excl_rcu (struct reservation_object*) ; 
 int reservation_object_get_fences_rcu (struct reservation_object*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int reservation_object_reserve_shared (struct reservation_object*) ; 

__attribute__((used)) static int submit_fence_sync(struct etnaviv_gem_submit *submit)
{
	int i, ret = 0;

	for (i = 0; i < submit->nr_bos; i++) {
		struct etnaviv_gem_submit_bo *bo = &submit->bos[i];
		struct reservation_object *robj = bo->obj->resv;

		if (!(bo->flags & ETNA_SUBMIT_BO_WRITE)) {
			ret = reservation_object_reserve_shared(robj);
			if (ret)
				return ret;
		}

		if (submit->flags & ETNA_SUBMIT_NO_IMPLICIT)
			continue;

		if (bo->flags & ETNA_SUBMIT_BO_WRITE) {
			ret = reservation_object_get_fences_rcu(robj, &bo->excl,
								&bo->nr_shared,
								&bo->shared);
			if (ret)
				return ret;
		} else {
			bo->excl = reservation_object_get_excl_rcu(robj);
		}

	}

	return ret;
}