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
struct mgag200_bo {int dummy; } ;
struct mga_framebuffer {struct drm_gem_object* obj; } ;
struct drm_gem_object {int dummy; } ;
struct drm_crtc {TYPE_1__* primary; } ;
struct TYPE_2__ {int /*<<< orphan*/ * fb; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG_KMS (char*) ; 
 int /*<<< orphan*/  DRM_MODE_DPMS_OFF ; 
 struct mgag200_bo* gem_to_mga_bo (struct drm_gem_object*) ; 
 int /*<<< orphan*/  mga_crtc_dpms (struct drm_crtc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mgag200_bo_push_sysram (struct mgag200_bo*) ; 
 int mgag200_bo_reserve (struct mgag200_bo*,int) ; 
 int /*<<< orphan*/  mgag200_bo_unreserve (struct mgag200_bo*) ; 
 struct mga_framebuffer* to_mga_framebuffer (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void mga_crtc_disable(struct drm_crtc *crtc)
{
	int ret;
	DRM_DEBUG_KMS("\n");
	mga_crtc_dpms(crtc, DRM_MODE_DPMS_OFF);
	if (crtc->primary->fb) {
		struct mga_framebuffer *mga_fb = to_mga_framebuffer(crtc->primary->fb);
		struct drm_gem_object *obj = mga_fb->obj;
		struct mgag200_bo *bo = gem_to_mga_bo(obj);
		ret = mgag200_bo_reserve(bo, false);
		if (ret)
			return;
		mgag200_bo_push_sysram(bo);
		mgag200_bo_unreserve(bo);
	}
	crtc->primary->fb = NULL;
}