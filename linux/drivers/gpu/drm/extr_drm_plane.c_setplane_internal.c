#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
struct drm_plane {int /*<<< orphan*/  dev; } ;
struct drm_modeset_acquire_ctx {int dummy; } ;
struct drm_framebuffer {int dummy; } ;
struct drm_crtc {int dummy; } ;
typedef  int /*<<< orphan*/  int32_t ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_MODESET_ACQUIRE_INTERRUPTIBLE ; 
 int /*<<< orphan*/  DRM_MODESET_LOCK_ALL_BEGIN (int /*<<< orphan*/ ,struct drm_modeset_acquire_ctx,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  DRM_MODESET_LOCK_ALL_END (struct drm_modeset_acquire_ctx,int) ; 
 int __setplane_atomic (struct drm_plane*,struct drm_crtc*,struct drm_framebuffer*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct drm_modeset_acquire_ctx*) ; 
 int __setplane_internal (struct drm_plane*,struct drm_crtc*,struct drm_framebuffer*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct drm_modeset_acquire_ctx*) ; 
 scalar_t__ drm_drv_uses_atomic_modeset (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int setplane_internal(struct drm_plane *plane,
			     struct drm_crtc *crtc,
			     struct drm_framebuffer *fb,
			     int32_t crtc_x, int32_t crtc_y,
			     uint32_t crtc_w, uint32_t crtc_h,
			     /* src_{x,y,w,h} values are 16.16 fixed point */
			     uint32_t src_x, uint32_t src_y,
			     uint32_t src_w, uint32_t src_h)
{
	struct drm_modeset_acquire_ctx ctx;
	int ret;

	DRM_MODESET_LOCK_ALL_BEGIN(plane->dev, ctx,
				   DRM_MODESET_ACQUIRE_INTERRUPTIBLE, ret);

	if (drm_drv_uses_atomic_modeset(plane->dev))
		ret = __setplane_atomic(plane, crtc, fb,
					crtc_x, crtc_y, crtc_w, crtc_h,
					src_x, src_y, src_w, src_h, &ctx);
	else
		ret = __setplane_internal(plane, crtc, fb,
					  crtc_x, crtc_y, crtc_w, crtc_h,
					  src_x, src_y, src_w, src_h, &ctx);

	DRM_MODESET_LOCK_ALL_END(ctx, ret);

	return ret;
}