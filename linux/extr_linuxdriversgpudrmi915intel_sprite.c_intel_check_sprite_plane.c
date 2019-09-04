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
typedef  int uint32_t ;
struct drm_rect {int x1; int y1; int x2; int y2; } ;
struct TYPE_9__ {int visible; struct drm_rect dst; struct drm_rect src; struct drm_framebuffer* fb; } ;
struct TYPE_7__ {int /*<<< orphan*/  flags; } ;
struct intel_plane_state {int /*<<< orphan*/  color_ctl; int /*<<< orphan*/  ctl; TYPE_4__ base; TYPE_2__ ckey; } ;
struct TYPE_6__ {int /*<<< orphan*/  dev; } ;
struct intel_plane {scalar_t__ pipe; int can_scale; int max_downscale; TYPE_1__ base; } ;
struct TYPE_10__ {int /*<<< orphan*/  crtc; } ;
struct intel_crtc_state {TYPE_5__ base; } ;
struct intel_crtc {scalar_t__ pipe; } ;
struct drm_i915_private {int dummy; } ;
struct drm_framebuffer {int width; int height; int* pitches; TYPE_3__* format; } ;
struct TYPE_8__ {int format; int* cpp; scalar_t__ is_yuv; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG_KMS (char*,...) ; 
 scalar_t__ DRM_FORMAT_NV12 ; 
 int DRM_PLANE_HELPER_NO_SCALING ; 
 int EINVAL ; 
 int INTEL_GEN (struct drm_i915_private*) ; 
 scalar_t__ IS_CHERRYVIEW (struct drm_i915_private*) ; 
 scalar_t__ IS_GEMINILAKE (struct drm_i915_private*) ; 
 scalar_t__ IS_VALLEYVIEW (struct drm_i915_private*) ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int drm_atomic_helper_check_plane_state (TYPE_4__*,TYPE_5__*,int,int,int,int) ; 
 int drm_rect_height (struct drm_rect*) ; 
 int drm_rect_width (struct drm_rect*) ; 
 int /*<<< orphan*/  g4x_sprite_ctl (struct intel_crtc_state*,struct intel_plane_state*) ; 
 int /*<<< orphan*/  glk_plane_color_ctl (struct intel_crtc_state*,struct intel_plane_state*) ; 
 int i9xx_check_plane_surface (struct intel_plane_state*) ; 
 int /*<<< orphan*/  ivb_sprite_ctl (struct intel_crtc_state*,struct intel_plane_state*) ; 
 int skl_check_plane_surface (struct intel_crtc_state*,struct intel_plane_state*) ; 
 int skl_max_scale (struct intel_crtc*,struct intel_crtc_state*,int) ; 
 int /*<<< orphan*/  skl_plane_ctl (struct intel_crtc_state*,struct intel_plane_state*) ; 
 struct drm_i915_private* to_i915 (int /*<<< orphan*/ ) ; 
 struct intel_crtc* to_intel_crtc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vlv_sprite_ctl (struct intel_crtc_state*,struct intel_plane_state*) ; 

__attribute__((used)) static int
intel_check_sprite_plane(struct intel_plane *plane,
			 struct intel_crtc_state *crtc_state,
			 struct intel_plane_state *state)
{
	struct drm_i915_private *dev_priv = to_i915(plane->base.dev);
	struct intel_crtc *crtc = to_intel_crtc(crtc_state->base.crtc);
	struct drm_framebuffer *fb = state->base.fb;
	int max_stride = INTEL_GEN(dev_priv) >= 9 ? 32768 : 16384;
	int max_scale, min_scale;
	bool can_scale;
	int ret;
	uint32_t pixel_format = 0;

	if (!fb) {
		state->base.visible = false;
		return 0;
	}

	/* Don't modify another pipe's plane */
	if (plane->pipe != crtc->pipe) {
		DRM_DEBUG_KMS("Wrong plane <-> crtc mapping\n");
		return -EINVAL;
	}

	/* FIXME check all gen limits */
	if (fb->width < 3 || fb->height < 3 || fb->pitches[0] > max_stride) {
		DRM_DEBUG_KMS("Unsuitable framebuffer for plane\n");
		return -EINVAL;
	}

	/* setup can_scale, min_scale, max_scale */
	if (INTEL_GEN(dev_priv) >= 9) {
		if (state->base.fb)
			pixel_format = state->base.fb->format->format;
		/* use scaler when colorkey is not required */
		if (!state->ckey.flags) {
			can_scale = 1;
			min_scale = 1;
			max_scale =
				skl_max_scale(crtc, crtc_state, pixel_format);
		} else {
			can_scale = 0;
			min_scale = DRM_PLANE_HELPER_NO_SCALING;
			max_scale = DRM_PLANE_HELPER_NO_SCALING;
		}
	} else {
		can_scale = plane->can_scale;
		max_scale = plane->max_downscale << 16;
		min_scale = plane->can_scale ? 1 : (1 << 16);
	}

	ret = drm_atomic_helper_check_plane_state(&state->base,
						  &crtc_state->base,
						  min_scale, max_scale,
						  true, true);
	if (ret)
		return ret;

	if (state->base.visible) {
		struct drm_rect *src = &state->base.src;
		struct drm_rect *dst = &state->base.dst;
		unsigned int crtc_w = drm_rect_width(dst);
		unsigned int crtc_h = drm_rect_height(dst);
		uint32_t src_x, src_y, src_w, src_h;

		/*
		 * Hardware doesn't handle subpixel coordinates.
		 * Adjust to (macro)pixel boundary, but be careful not to
		 * increase the source viewport size, because that could
		 * push the downscaling factor out of bounds.
		 */
		src_x = src->x1 >> 16;
		src_w = drm_rect_width(src) >> 16;
		src_y = src->y1 >> 16;
		src_h = drm_rect_height(src) >> 16;

		src->x1 = src_x << 16;
		src->x2 = (src_x + src_w) << 16;
		src->y1 = src_y << 16;
		src->y2 = (src_y + src_h) << 16;

		if (fb->format->is_yuv &&
    		    fb->format->format != DRM_FORMAT_NV12 &&
		    (src_x % 2 || src_w % 2)) {
			DRM_DEBUG_KMS("src x/w (%u, %u) must be a multiple of 2 for YUV planes\n",
				      src_x, src_w);
			return -EINVAL;
		}

		/* Check size restrictions when scaling */
		if (src_w != crtc_w || src_h != crtc_h) {
			unsigned int width_bytes;
			int cpp = fb->format->cpp[0];

			WARN_ON(!can_scale);

			width_bytes = ((src_x * cpp) & 63) + src_w * cpp;

			/* FIXME interlacing min height is 6 */
			if (INTEL_GEN(dev_priv) < 9 && (
			     src_w < 3 || src_h < 3 ||
			     src_w > 2048 || src_h > 2048 ||
			     crtc_w < 3 || crtc_h < 3 ||
			     width_bytes > 4096 || fb->pitches[0] > 4096)) {
				DRM_DEBUG_KMS("Source dimensions exceed hardware limits\n");
				return -EINVAL;
			}
		}
	}

	if (INTEL_GEN(dev_priv) >= 9) {
		ret = skl_check_plane_surface(crtc_state, state);
		if (ret)
			return ret;

		state->ctl = skl_plane_ctl(crtc_state, state);
	} else if (IS_VALLEYVIEW(dev_priv) || IS_CHERRYVIEW(dev_priv)) {
		ret = i9xx_check_plane_surface(state);
		if (ret)
			return ret;

		state->ctl = vlv_sprite_ctl(crtc_state, state);
	} else if (INTEL_GEN(dev_priv) >= 7) {
		ret = i9xx_check_plane_surface(state);
		if (ret)
			return ret;

		state->ctl = ivb_sprite_ctl(crtc_state, state);
	} else {
		ret = i9xx_check_plane_surface(state);
		if (ret)
			return ret;

		state->ctl = g4x_sprite_ctl(crtc_state, state);
	}

	if (INTEL_GEN(dev_priv) >= 10 || IS_GEMINILAKE(dev_priv))
		state->color_ctl = glk_plane_color_ctl(crtc_state, state);

	return 0;
}