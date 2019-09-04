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
struct msm_gpu {int /*<<< orphan*/  active_list; } ;
struct msm_gem_object {scalar_t__ madv; int /*<<< orphan*/  mm_list; int /*<<< orphan*/  resv; struct msm_gpu* gpu; } ;
struct drm_gem_object {int dummy; } ;
struct dma_fence {int dummy; } ;

/* Variables and functions */
 scalar_t__ MSM_MADV_WILLNEED ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_del_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  reservation_object_add_excl_fence (int /*<<< orphan*/ ,struct dma_fence*) ; 
 int /*<<< orphan*/  reservation_object_add_shared_fence (int /*<<< orphan*/ ,struct dma_fence*) ; 
 struct msm_gem_object* to_msm_bo (struct drm_gem_object*) ; 

void msm_gem_move_to_active(struct drm_gem_object *obj,
		struct msm_gpu *gpu, bool exclusive, struct dma_fence *fence)
{
	struct msm_gem_object *msm_obj = to_msm_bo(obj);
	WARN_ON(msm_obj->madv != MSM_MADV_WILLNEED);
	msm_obj->gpu = gpu;
	if (exclusive)
		reservation_object_add_excl_fence(msm_obj->resv, fence);
	else
		reservation_object_add_shared_fence(msm_obj->resv, fence);
	list_del_init(&msm_obj->mm_list);
	list_add_tail(&msm_obj->mm_list, &gpu->active_list);
}