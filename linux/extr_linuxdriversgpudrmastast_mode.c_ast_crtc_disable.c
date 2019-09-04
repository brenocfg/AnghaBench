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
struct drm_gem_object {int dummy; } ;
struct drm_crtc {TYPE_1__* primary; } ;
struct ast_framebuffer {struct drm_gem_object* obj; } ;
struct ast_bo {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/ * fb; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG_KMS (char*) ; 
 int /*<<< orphan*/  DRM_MODE_DPMS_OFF ; 
 int /*<<< orphan*/  ast_bo_push_sysram (struct ast_bo*) ; 
 int ast_bo_reserve (struct ast_bo*,int) ; 
 int /*<<< orphan*/  ast_bo_unreserve (struct ast_bo*) ; 
 int /*<<< orphan*/  ast_crtc_dpms (struct drm_crtc*,int /*<<< orphan*/ ) ; 
 struct ast_bo* gem_to_ast_bo (struct drm_gem_object*) ; 
 struct ast_framebuffer* to_ast_framebuffer (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ast_crtc_disable(struct drm_crtc *crtc)
{
	int ret;

	DRM_DEBUG_KMS("\n");
	ast_crtc_dpms(crtc, DRM_MODE_DPMS_OFF);
	if (crtc->primary->fb) {
		struct ast_framebuffer *ast_fb = to_ast_framebuffer(crtc->primary->fb);
		struct drm_gem_object *obj = ast_fb->obj;
		struct ast_bo *bo = gem_to_ast_bo(obj);

		ret = ast_bo_reserve(bo, false);
		if (ret)
			return;

		ast_bo_push_sysram(bo);
		ast_bo_unreserve(bo);
	}
	crtc->primary->fb = NULL;
}