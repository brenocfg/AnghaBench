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
struct drm_gem_vram_object {int dummy; } ;
struct drm_framebuffer {int /*<<< orphan*/ * obj; } ;
struct drm_crtc {TYPE_1__* primary; } ;
struct TYPE_2__ {struct drm_framebuffer* fb; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG_KMS (char*) ; 
 int /*<<< orphan*/  DRM_MODE_DPMS_OFF ; 
 int /*<<< orphan*/  ast_crtc_dpms (struct drm_crtc*,int /*<<< orphan*/ ) ; 
 struct drm_gem_vram_object* drm_gem_vram_of_gem (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_gem_vram_unpin (struct drm_gem_vram_object*) ; 

__attribute__((used)) static void ast_crtc_disable(struct drm_crtc *crtc)
{
	DRM_DEBUG_KMS("\n");
	ast_crtc_dpms(crtc, DRM_MODE_DPMS_OFF);
	if (crtc->primary->fb) {
		struct drm_framebuffer *fb = crtc->primary->fb;
		struct drm_gem_vram_object *gbo =
			drm_gem_vram_of_gem(fb->obj[0]);

		drm_gem_vram_unpin(gbo);
	}
	crtc->primary->fb = NULL;
}