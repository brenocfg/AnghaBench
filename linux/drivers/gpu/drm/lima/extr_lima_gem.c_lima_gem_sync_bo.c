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
struct lima_sched_task {int /*<<< orphan*/  deps; } ;
struct TYPE_2__ {int /*<<< orphan*/  resv; } ;
struct lima_bo {TYPE_1__ gem; } ;

/* Variables and functions */
 int dma_resv_reserve_shared (int /*<<< orphan*/ ,int) ; 
 int drm_gem_fence_array_add_implicit (int /*<<< orphan*/ *,TYPE_1__*,int) ; 

__attribute__((used)) static int lima_gem_sync_bo(struct lima_sched_task *task, struct lima_bo *bo,
			    bool write, bool explicit)
{
	int err = 0;

	if (!write) {
		err = dma_resv_reserve_shared(bo->gem.resv, 1);
		if (err)
			return err;
	}

	/* explicit sync use user passed dep fence */
	if (explicit)
		return 0;

	return drm_gem_fence_array_add_implicit(&task->deps, &bo->gem, write);
}