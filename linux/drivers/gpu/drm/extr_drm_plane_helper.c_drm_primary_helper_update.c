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
typedef  int uint32_t ;
struct drm_rect {int x1; int y1; int x2; int y2; } ;
struct drm_plane {TYPE_1__* funcs; } ;
struct drm_modeset_acquire_ctx {int dummy; } ;
struct drm_mode_set {int x; int y; int num_connectors; struct drm_connector** connectors; int /*<<< orphan*/ * mode; struct drm_framebuffer* fb; struct drm_crtc* crtc; } ;
struct drm_framebuffer {int dummy; } ;
struct drm_crtc {TYPE_2__* funcs; int /*<<< orphan*/  mode; } ;
struct drm_connector {int dummy; } ;
struct TYPE_4__ {int (* set_config ) (struct drm_mode_set*,struct drm_modeset_acquire_ctx*) ;} ;
struct TYPE_3__ {int (* disable_plane ) (struct drm_plane*,struct drm_modeset_acquire_ctx*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  DRM_MODE_ROTATE_0 ; 
 int /*<<< orphan*/  DRM_PLANE_HELPER_NO_SCALING ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int drm_plane_helper_check_update (struct drm_plane*,struct drm_crtc*,struct drm_framebuffer*,struct drm_rect*,struct drm_rect*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int*) ; 
 int get_connectors_for_crtc (struct drm_crtc*,struct drm_connector**,int) ; 
 struct drm_connector** kcalloc (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct drm_connector**) ; 
 int stub1 (struct drm_plane*,struct drm_modeset_acquire_ctx*) ; 
 int stub2 (struct drm_mode_set*,struct drm_modeset_acquire_ctx*) ; 

__attribute__((used)) static int drm_primary_helper_update(struct drm_plane *plane, struct drm_crtc *crtc,
				     struct drm_framebuffer *fb,
				     int crtc_x, int crtc_y,
				     unsigned int crtc_w, unsigned int crtc_h,
				     uint32_t src_x, uint32_t src_y,
				     uint32_t src_w, uint32_t src_h,
				     struct drm_modeset_acquire_ctx *ctx)
{
	struct drm_mode_set set = {
		.crtc = crtc,
		.fb = fb,
		.mode = &crtc->mode,
		.x = src_x >> 16,
		.y = src_y >> 16,
	};
	struct drm_rect src = {
		.x1 = src_x,
		.y1 = src_y,
		.x2 = src_x + src_w,
		.y2 = src_y + src_h,
	};
	struct drm_rect dest = {
		.x1 = crtc_x,
		.y1 = crtc_y,
		.x2 = crtc_x + crtc_w,
		.y2 = crtc_y + crtc_h,
	};
	struct drm_connector **connector_list;
	int num_connectors, ret;
	bool visible;

	ret = drm_plane_helper_check_update(plane, crtc, fb,
					    &src, &dest,
					    DRM_MODE_ROTATE_0,
					    DRM_PLANE_HELPER_NO_SCALING,
					    DRM_PLANE_HELPER_NO_SCALING,
					    false, false, &visible);
	if (ret)
		return ret;

	if (!visible)
		/*
		 * Primary plane isn't visible.  Note that unless a driver
		 * provides their own disable function, this will just
		 * wind up returning -EINVAL to userspace.
		 */
		return plane->funcs->disable_plane(plane, ctx);

	/* Find current connectors for CRTC */
	num_connectors = get_connectors_for_crtc(crtc, NULL, 0);
	BUG_ON(num_connectors == 0);
	connector_list = kcalloc(num_connectors, sizeof(*connector_list),
				 GFP_KERNEL);
	if (!connector_list)
		return -ENOMEM;
	get_connectors_for_crtc(crtc, connector_list, num_connectors);

	set.connectors = connector_list;
	set.num_connectors = num_connectors;

	/*
	 * We call set_config() directly here rather than using
	 * drm_mode_set_config_internal.  We're reprogramming the same
	 * connectors that were already in use, so we shouldn't need the extra
	 * cross-CRTC fb refcounting to accomodate stealing connectors.
	 * drm_mode_setplane() already handles the basic refcounting for the
	 * framebuffers involved in this operation.
	 */
	ret = crtc->funcs->set_config(&set, ctx);

	kfree(connector_list);
	return ret;
}