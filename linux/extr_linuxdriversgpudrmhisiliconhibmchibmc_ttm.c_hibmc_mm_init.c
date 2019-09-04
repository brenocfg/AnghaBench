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
struct ttm_bo_device {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  object; } ;
struct TYPE_5__ {TYPE_1__ ref; } ;
struct hibmc_drm_private {int fb_size; int mm_inited; TYPE_2__ bo_global_ref; struct ttm_bo_device bdev; struct drm_device* dev; } ;
struct drm_device {TYPE_3__* anon_inode; } ;
struct TYPE_6__ {int /*<<< orphan*/  i_mapping; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_ERROR (char*,int) ; 
 int /*<<< orphan*/  DRM_FILE_PAGE_OFFSET ; 
 int PAGE_SHIFT ; 
 int /*<<< orphan*/  TTM_PL_VRAM ; 
 int /*<<< orphan*/  hibmc_bo_driver ; 
 int hibmc_ttm_global_init (struct hibmc_drm_private*) ; 
 int /*<<< orphan*/  hibmc_ttm_global_release (struct hibmc_drm_private*) ; 
 int ttm_bo_device_init (struct ttm_bo_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int ttm_bo_init_mm (struct ttm_bo_device*,int /*<<< orphan*/ ,int) ; 

int hibmc_mm_init(struct hibmc_drm_private *hibmc)
{
	int ret;
	struct drm_device *dev = hibmc->dev;
	struct ttm_bo_device *bdev = &hibmc->bdev;

	ret = hibmc_ttm_global_init(hibmc);
	if (ret)
		return ret;

	ret = ttm_bo_device_init(&hibmc->bdev,
				 hibmc->bo_global_ref.ref.object,
				 &hibmc_bo_driver,
				 dev->anon_inode->i_mapping,
				 DRM_FILE_PAGE_OFFSET,
				 true);
	if (ret) {
		hibmc_ttm_global_release(hibmc);
		DRM_ERROR("error initializing bo driver: %d\n", ret);
		return ret;
	}

	ret = ttm_bo_init_mm(bdev, TTM_PL_VRAM,
			     hibmc->fb_size >> PAGE_SHIFT);
	if (ret) {
		hibmc_ttm_global_release(hibmc);
		DRM_ERROR("failed ttm VRAM init: %d\n", ret);
		return ret;
	}

	hibmc->mm_inited = true;
	return 0;
}