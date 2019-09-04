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
typedef  int uint32_t ;
struct drm_plane {struct drm_framebuffer* fb; TYPE_1__* state; struct drm_crtc* crtc; } ;
struct drm_modeset_acquire_ctx {int dummy; } ;
struct drm_mode_fb_cmd2 {int /*<<< orphan*/  handles; int /*<<< orphan*/  pitches; int /*<<< orphan*/  pixel_format; int /*<<< orphan*/  height; int /*<<< orphan*/  width; } ;
struct drm_mode_cursor2 {int flags; int /*<<< orphan*/  y; int /*<<< orphan*/  x; int /*<<< orphan*/  hot_y; int /*<<< orphan*/  hot_x; scalar_t__ handle; int /*<<< orphan*/  height; int /*<<< orphan*/  width; } ;
struct drm_framebuffer {int width; int height; int /*<<< orphan*/  hot_y; int /*<<< orphan*/  hot_x; } ;
struct drm_file {int dummy; } ;
struct drm_device {int dummy; } ;
struct drm_crtc {int /*<<< orphan*/  cursor_y; int /*<<< orphan*/  cursor_x; struct drm_plane* cursor; struct drm_device* dev; } ;
typedef  int /*<<< orphan*/  int32_t ;
struct TYPE_2__ {struct drm_framebuffer* fb; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  DRM_DEBUG_KMS (char*) ; 
 int /*<<< orphan*/  DRM_FORMAT_ARGB8888 ; 
 int DRM_MODE_CURSOR_BO ; 
 int DRM_MODE_CURSOR_MOVE ; 
 scalar_t__ IS_ERR (struct drm_framebuffer*) ; 
 int PTR_ERR (struct drm_framebuffer*) ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int __setplane_atomic (struct drm_plane*,struct drm_crtc*,struct drm_framebuffer*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,struct drm_modeset_acquire_ctx*) ; 
 int __setplane_internal (struct drm_plane*,struct drm_crtc*,struct drm_framebuffer*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,struct drm_modeset_acquire_ctx*) ; 
 scalar_t__ drm_drv_uses_atomic_modeset (struct drm_device*) ; 
 int /*<<< orphan*/  drm_framebuffer_get (struct drm_framebuffer*) ; 
 int /*<<< orphan*/  drm_framebuffer_put (struct drm_framebuffer*) ; 
 struct drm_framebuffer* drm_internal_framebuffer_create (struct drm_device*,struct drm_mode_fb_cmd2*,struct drm_file*) ; 

__attribute__((used)) static int drm_mode_cursor_universal(struct drm_crtc *crtc,
				     struct drm_mode_cursor2 *req,
				     struct drm_file *file_priv,
				     struct drm_modeset_acquire_ctx *ctx)
{
	struct drm_device *dev = crtc->dev;
	struct drm_plane *plane = crtc->cursor;
	struct drm_framebuffer *fb = NULL;
	struct drm_mode_fb_cmd2 fbreq = {
		.width = req->width,
		.height = req->height,
		.pixel_format = DRM_FORMAT_ARGB8888,
		.pitches = { req->width * 4 },
		.handles = { req->handle },
	};
	int32_t crtc_x, crtc_y;
	uint32_t crtc_w = 0, crtc_h = 0;
	uint32_t src_w = 0, src_h = 0;
	int ret = 0;

	BUG_ON(!plane);
	WARN_ON(plane->crtc != crtc && plane->crtc != NULL);

	/*
	 * Obtain fb we'll be using (either new or existing) and take an extra
	 * reference to it if fb != null.  setplane will take care of dropping
	 * the reference if the plane update fails.
	 */
	if (req->flags & DRM_MODE_CURSOR_BO) {
		if (req->handle) {
			fb = drm_internal_framebuffer_create(dev, &fbreq, file_priv);
			if (IS_ERR(fb)) {
				DRM_DEBUG_KMS("failed to wrap cursor buffer in drm framebuffer\n");
				return PTR_ERR(fb);
			}

			fb->hot_x = req->hot_x;
			fb->hot_y = req->hot_y;
		} else {
			fb = NULL;
		}
	} else {
		if (plane->state)
			fb = plane->state->fb;
		else
			fb = plane->fb;

		if (fb)
			drm_framebuffer_get(fb);
	}

	if (req->flags & DRM_MODE_CURSOR_MOVE) {
		crtc_x = req->x;
		crtc_y = req->y;
	} else {
		crtc_x = crtc->cursor_x;
		crtc_y = crtc->cursor_y;
	}

	if (fb) {
		crtc_w = fb->width;
		crtc_h = fb->height;
		src_w = fb->width << 16;
		src_h = fb->height << 16;
	}

	if (drm_drv_uses_atomic_modeset(dev))
		ret = __setplane_atomic(plane, crtc, fb,
					crtc_x, crtc_y, crtc_w, crtc_h,
					0, 0, src_w, src_h, ctx);
	else
		ret = __setplane_internal(plane, crtc, fb,
					  crtc_x, crtc_y, crtc_w, crtc_h,
					  0, 0, src_w, src_h, ctx);

	if (fb)
		drm_framebuffer_put(fb);

	/* Update successful; save new cursor position, if necessary */
	if (ret == 0 && req->flags & DRM_MODE_CURSOR_MOVE) {
		crtc->cursor_x = req->x;
		crtc->cursor_y = req->y;
	}

	return ret;
}