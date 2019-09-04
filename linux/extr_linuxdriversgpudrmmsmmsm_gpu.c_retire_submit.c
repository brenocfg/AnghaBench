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
struct msm_gpu {TYPE_1__* pdev; int /*<<< orphan*/  aspace; } ;
struct msm_gem_submit {int nr_bos; TYPE_2__* bos; } ;
struct msm_gem_object {int /*<<< orphan*/  base; } ;
struct TYPE_4__ {struct msm_gem_object* obj; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  drm_gem_object_put (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  msm_gem_move_to_inactive (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  msm_gem_put_iova (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msm_gem_submit_free (struct msm_gem_submit*) ; 
 int /*<<< orphan*/  pm_runtime_mark_last_busy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_runtime_put_autosuspend (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void retire_submit(struct msm_gpu *gpu, struct msm_gem_submit *submit)
{
	int i;

	for (i = 0; i < submit->nr_bos; i++) {
		struct msm_gem_object *msm_obj = submit->bos[i].obj;
		/* move to inactive: */
		msm_gem_move_to_inactive(&msm_obj->base);
		msm_gem_put_iova(&msm_obj->base, gpu->aspace);
		drm_gem_object_put(&msm_obj->base);
	}

	pm_runtime_mark_last_busy(&gpu->pdev->dev);
	pm_runtime_put_autosuspend(&gpu->pdev->dev);
	msm_gem_submit_free(submit);
}