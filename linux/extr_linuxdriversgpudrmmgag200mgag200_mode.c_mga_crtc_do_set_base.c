#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u64 ;
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_8__ {int /*<<< orphan*/  num_pages; } ;
struct mgag200_bo {int /*<<< orphan*/  kmap; TYPE_4__ bo; } ;
struct mga_framebuffer {struct drm_gem_object* obj; } ;
struct mga_device {TYPE_3__* mfbdev; } ;
struct drm_gem_object {int dummy; } ;
struct drm_framebuffer {int dummy; } ;
struct drm_crtc {TYPE_2__* primary; TYPE_1__* dev; } ;
struct TYPE_7__ {struct mga_framebuffer mfb; } ;
struct TYPE_6__ {struct drm_framebuffer* fb; } ;
struct TYPE_5__ {struct mga_device* dev_private; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_ERROR (char*) ; 
 int /*<<< orphan*/  TTM_PL_FLAG_VRAM ; 
 struct mgag200_bo* gem_to_mga_bo (struct drm_gem_object*) ; 
 int /*<<< orphan*/  mga_set_start_address (struct drm_crtc*,int /*<<< orphan*/ ) ; 
 int mgag200_bo_pin (struct mgag200_bo*,int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  mgag200_bo_push_sysram (struct mgag200_bo*) ; 
 int mgag200_bo_reserve (struct mgag200_bo*,int) ; 
 int /*<<< orphan*/  mgag200_bo_unreserve (struct mgag200_bo*) ; 
 struct mga_framebuffer* to_mga_framebuffer (struct drm_framebuffer*) ; 
 int ttm_bo_kmap (TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int mga_crtc_do_set_base(struct drm_crtc *crtc,
				struct drm_framebuffer *fb,
				int x, int y, int atomic)
{
	struct mga_device *mdev = crtc->dev->dev_private;
	struct drm_gem_object *obj;
	struct mga_framebuffer *mga_fb;
	struct mgag200_bo *bo;
	int ret;
	u64 gpu_addr;

	/* push the previous fb to system ram */
	if (!atomic && fb) {
		mga_fb = to_mga_framebuffer(fb);
		obj = mga_fb->obj;
		bo = gem_to_mga_bo(obj);
		ret = mgag200_bo_reserve(bo, false);
		if (ret)
			return ret;
		mgag200_bo_push_sysram(bo);
		mgag200_bo_unreserve(bo);
	}

	mga_fb = to_mga_framebuffer(crtc->primary->fb);
	obj = mga_fb->obj;
	bo = gem_to_mga_bo(obj);

	ret = mgag200_bo_reserve(bo, false);
	if (ret)
		return ret;

	ret = mgag200_bo_pin(bo, TTM_PL_FLAG_VRAM, &gpu_addr);
	if (ret) {
		mgag200_bo_unreserve(bo);
		return ret;
	}

	if (&mdev->mfbdev->mfb == mga_fb) {
		/* if pushing console in kmap it */
		ret = ttm_bo_kmap(&bo->bo, 0, bo->bo.num_pages, &bo->kmap);
		if (ret)
			DRM_ERROR("failed to kmap fbcon\n");

	}
	mgag200_bo_unreserve(bo);

	mga_set_start_address(crtc, (u32)gpu_addr);

	return 0;
}