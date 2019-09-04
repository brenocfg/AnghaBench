#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u64 ;
typedef  int /*<<< orphan*/  u32 ;
struct drm_framebuffer {int /*<<< orphan*/ * obj; } ;
struct drm_crtc {TYPE_5__* primary; TYPE_1__* dev; } ;
struct TYPE_9__ {TYPE_2__* gfbdev; } ;
struct cirrus_device {TYPE_3__ mode_info; } ;
struct TYPE_12__ {int /*<<< orphan*/  num_pages; } ;
struct cirrus_bo {int /*<<< orphan*/  kmap; TYPE_6__ bo; } ;
struct TYPE_11__ {TYPE_4__* fb; } ;
struct TYPE_10__ {int /*<<< orphan*/ * obj; } ;
struct TYPE_8__ {TYPE_4__* gfb; } ;
struct TYPE_7__ {struct cirrus_device* dev_private; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_ERROR (char*) ; 
 int /*<<< orphan*/  TTM_PL_FLAG_VRAM ; 
 int cirrus_bo_pin (struct cirrus_bo*,int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  cirrus_bo_push_sysram (struct cirrus_bo*) ; 
 int cirrus_bo_reserve (struct cirrus_bo*,int) ; 
 int /*<<< orphan*/  cirrus_bo_unreserve (struct cirrus_bo*) ; 
 int /*<<< orphan*/  cirrus_set_start_address (struct drm_crtc*,int /*<<< orphan*/ ) ; 
 struct cirrus_bo* gem_to_cirrus_bo (int /*<<< orphan*/ ) ; 
 int ttm_bo_kmap (TYPE_6__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int cirrus_crtc_do_set_base(struct drm_crtc *crtc,
				struct drm_framebuffer *fb,
				int x, int y, int atomic)
{
	struct cirrus_device *cdev = crtc->dev->dev_private;
	struct cirrus_bo *bo;
	int ret;
	u64 gpu_addr;

	/* push the previous fb to system ram */
	if (!atomic && fb) {
		bo = gem_to_cirrus_bo(fb->obj[0]);
		ret = cirrus_bo_reserve(bo, false);
		if (ret)
			return ret;
		cirrus_bo_push_sysram(bo);
		cirrus_bo_unreserve(bo);
	}

	bo = gem_to_cirrus_bo(crtc->primary->fb->obj[0]);

	ret = cirrus_bo_reserve(bo, false);
	if (ret)
		return ret;

	ret = cirrus_bo_pin(bo, TTM_PL_FLAG_VRAM, &gpu_addr);
	if (ret) {
		cirrus_bo_unreserve(bo);
		return ret;
	}

	if (cdev->mode_info.gfbdev->gfb == crtc->primary->fb) {
		/* if pushing console in kmap it */
		ret = ttm_bo_kmap(&bo->bo, 0, bo->bo.num_pages, &bo->kmap);
		if (ret)
			DRM_ERROR("failed to kmap fbcon\n");
	}
	cirrus_bo_unreserve(bo);

	cirrus_set_start_address(crtc, (u32)gpu_addr);
	return 0;
}