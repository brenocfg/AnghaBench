#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct msm_gpu {TYPE_3__* aspace; int /*<<< orphan*/  memptrs_bo; int /*<<< orphan*/ ** rb; int /*<<< orphan*/  active_list; int /*<<< orphan*/  name; } ;
struct TYPE_8__ {TYPE_2__* mmu; } ;
struct TYPE_7__ {TYPE_1__* funcs; } ;
struct TYPE_6__ {int /*<<< orphan*/  (* detach ) (TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int ARRAY_SIZE (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  DBG (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IS_ERR_OR_NULL (TYPE_3__*) ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  msm_gem_address_space_put (TYPE_3__*) ; 
 int /*<<< orphan*/  msm_gem_kernel_put (int /*<<< orphan*/ ,TYPE_3__*,int) ; 
 int /*<<< orphan*/  msm_ringbuffer_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void msm_gpu_cleanup(struct msm_gpu *gpu)
{
	int i;

	DBG("%s", gpu->name);

	WARN_ON(!list_empty(&gpu->active_list));

	for (i = 0; i < ARRAY_SIZE(gpu->rb); i++) {
		msm_ringbuffer_destroy(gpu->rb[i]);
		gpu->rb[i] = NULL;
	}

	msm_gem_kernel_put(gpu->memptrs_bo, gpu->aspace, false);

	if (!IS_ERR_OR_NULL(gpu->aspace)) {
		gpu->aspace->mmu->funcs->detach(gpu->aspace->mmu,
			NULL, 0);
		msm_gem_address_space_put(gpu->aspace);
	}
}