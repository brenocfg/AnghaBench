#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct ttm_bo_device {int dummy; } ;
struct TYPE_6__ {int /*<<< orphan*/  object; } ;
struct TYPE_7__ {TYPE_1__ ref; } ;
struct TYPE_10__ {int initialized; TYPE_2__ bo_global_ref; struct ttm_bo_device bdev; } ;
struct bochs_device {int fb_size; TYPE_5__ ttm; TYPE_4__* dev; } ;
struct TYPE_9__ {TYPE_3__* anon_inode; } ;
struct TYPE_8__ {int /*<<< orphan*/  i_mapping; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_ERROR (char*,int) ; 
 int /*<<< orphan*/  DRM_FILE_PAGE_OFFSET ; 
 int PAGE_SHIFT ; 
 int /*<<< orphan*/  TTM_PL_VRAM ; 
 int /*<<< orphan*/  bochs_bo_driver ; 
 int bochs_ttm_global_init (struct bochs_device*) ; 
 int ttm_bo_device_init (struct ttm_bo_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int ttm_bo_init_mm (struct ttm_bo_device*,int /*<<< orphan*/ ,int) ; 

int bochs_mm_init(struct bochs_device *bochs)
{
	struct ttm_bo_device *bdev = &bochs->ttm.bdev;
	int ret;

	ret = bochs_ttm_global_init(bochs);
	if (ret)
		return ret;

	ret = ttm_bo_device_init(&bochs->ttm.bdev,
				 bochs->ttm.bo_global_ref.ref.object,
				 &bochs_bo_driver,
				 bochs->dev->anon_inode->i_mapping,
				 DRM_FILE_PAGE_OFFSET,
				 true);
	if (ret) {
		DRM_ERROR("Error initialising bo driver; %d\n", ret);
		return ret;
	}

	ret = ttm_bo_init_mm(bdev, TTM_PL_VRAM,
			     bochs->fb_size >> PAGE_SHIFT);
	if (ret) {
		DRM_ERROR("Failed ttm VRAM init: %d\n", ret);
		return ret;
	}

	bochs->ttm.initialized = true;
	return 0;
}