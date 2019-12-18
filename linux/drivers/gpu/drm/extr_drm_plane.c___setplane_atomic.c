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
typedef  int /*<<< orphan*/  uint32_t ;
struct drm_plane {TYPE_1__* funcs; int /*<<< orphan*/  dev; } ;
struct drm_modeset_acquire_ctx {int dummy; } ;
struct drm_framebuffer {int dummy; } ;
struct drm_crtc {int dummy; } ;
typedef  int /*<<< orphan*/  int32_t ;
struct TYPE_2__ {int (* disable_plane ) (struct drm_plane*,struct drm_modeset_acquire_ctx*) ;int (* update_plane ) (struct drm_plane*,struct drm_crtc*,struct drm_framebuffer*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct drm_modeset_acquire_ctx*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (int) ; 
 int __setplane_check (struct drm_plane*,struct drm_crtc*,struct drm_framebuffer*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_drv_uses_atomic_modeset (int /*<<< orphan*/ ) ; 
 int stub1 (struct drm_plane*,struct drm_modeset_acquire_ctx*) ; 
 int stub2 (struct drm_plane*,struct drm_crtc*,struct drm_framebuffer*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct drm_modeset_acquire_ctx*) ; 

__attribute__((used)) static int __setplane_atomic(struct drm_plane *plane,
			     struct drm_crtc *crtc,
			     struct drm_framebuffer *fb,
			     int32_t crtc_x, int32_t crtc_y,
			     uint32_t crtc_w, uint32_t crtc_h,
			     uint32_t src_x, uint32_t src_y,
			     uint32_t src_w, uint32_t src_h,
			     struct drm_modeset_acquire_ctx *ctx)
{
	int ret;

	WARN_ON(!drm_drv_uses_atomic_modeset(plane->dev));

	/* No fb means shut it down */
	if (!fb)
		return plane->funcs->disable_plane(plane, ctx);

	/*
	 * FIXME: This is redundant with drm_atomic_plane_check(),
	 * but the legacy cursor/"async" .update_plane() tricks
	 * don't call that so we still need this here. Should remove
	 * this when all .update_plane() implementations have been
	 * fixed to call drm_atomic_plane_check().
	 */
	ret = __setplane_check(plane, crtc, fb,
			       crtc_x, crtc_y, crtc_w, crtc_h,
			       src_x, src_y, src_w, src_h);
	if (ret)
		return ret;

	return plane->funcs->update_plane(plane, crtc, fb,
					  crtc_x, crtc_y, crtc_w, crtc_h,
					  src_x, src_y, src_w, src_h, ctx);
}