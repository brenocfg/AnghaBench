#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct ttm_mem_global {int dummy; } ;
struct ttm_bo_global {int dummy; } ;
struct TYPE_5__ {int size; int /*<<< orphan*/ * release; int /*<<< orphan*/ * init; int /*<<< orphan*/  global_type; int /*<<< orphan*/  object; } ;
struct TYPE_4__ {TYPE_2__ ref; int /*<<< orphan*/  mem_glob; } ;
struct hibmc_drm_private {TYPE_2__ mem_global_ref; TYPE_1__ bo_global_ref; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_ERROR (char*,int) ; 
 int /*<<< orphan*/  DRM_GLOBAL_TTM_BO ; 
 int /*<<< orphan*/  DRM_GLOBAL_TTM_MEM ; 
 int drm_global_item_ref (TYPE_2__*) ; 
 int /*<<< orphan*/  drm_global_item_unref (TYPE_2__*) ; 
 int /*<<< orphan*/  hibmc_ttm_mem_global_init ; 
 int /*<<< orphan*/  hibmc_ttm_mem_global_release ; 
 int /*<<< orphan*/  ttm_bo_global_init ; 
 int /*<<< orphan*/  ttm_bo_global_release ; 

__attribute__((used)) static int hibmc_ttm_global_init(struct hibmc_drm_private *hibmc)
{
	int ret;

	hibmc->mem_global_ref.global_type = DRM_GLOBAL_TTM_MEM;
	hibmc->mem_global_ref.size = sizeof(struct ttm_mem_global);
	hibmc->mem_global_ref.init = &hibmc_ttm_mem_global_init;
	hibmc->mem_global_ref.release = &hibmc_ttm_mem_global_release;
	ret = drm_global_item_ref(&hibmc->mem_global_ref);
	if (ret) {
		DRM_ERROR("could not get ref on ttm global: %d\n", ret);
		return ret;
	}

	hibmc->bo_global_ref.mem_glob =
		hibmc->mem_global_ref.object;
	hibmc->bo_global_ref.ref.global_type = DRM_GLOBAL_TTM_BO;
	hibmc->bo_global_ref.ref.size = sizeof(struct ttm_bo_global);
	hibmc->bo_global_ref.ref.init = &ttm_bo_global_init;
	hibmc->bo_global_ref.ref.release = &ttm_bo_global_release;
	ret = drm_global_item_ref(&hibmc->bo_global_ref.ref);
	if (ret) {
		DRM_ERROR("failed setting up TTM BO subsystem: %d\n", ret);
		drm_global_item_unref(&hibmc->mem_global_ref);
		return ret;
	}
	return 0;
}