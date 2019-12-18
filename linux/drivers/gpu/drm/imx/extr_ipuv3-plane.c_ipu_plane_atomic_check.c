#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int x1; int y1; } ;
struct drm_plane_state {TYPE_2__ src; int /*<<< orphan*/  dst; int /*<<< orphan*/  crtc; int /*<<< orphan*/  state; struct drm_framebuffer* fb; } ;
struct drm_plane {int type; TYPE_1__* dev; struct drm_plane_state* state; } ;
struct drm_framebuffer {int* pitches; TYPE_3__* format; } ;
struct drm_crtc_state {int mode_changed; int /*<<< orphan*/  enable; } ;
struct device {int dummy; } ;
struct TYPE_6__ {int format; int /*<<< orphan*/  vsub; int /*<<< orphan*/  hsub; } ;
struct TYPE_4__ {struct device* dev; } ;

/* Variables and functions */
#define  DRM_FORMAT_BGR565_A8 143 
#define  DRM_FORMAT_BGR888_A8 142 
#define  DRM_FORMAT_BGRX8888_A8 141 
#define  DRM_FORMAT_NV12 140 
#define  DRM_FORMAT_NV16 139 
#define  DRM_FORMAT_RGB565_A8 138 
#define  DRM_FORMAT_RGB888_A8 137 
#define  DRM_FORMAT_RGBX8888_A8 136 
#define  DRM_FORMAT_YUV420 135 
#define  DRM_FORMAT_YUV422 134 
#define  DRM_FORMAT_YUV444 133 
#define  DRM_FORMAT_YVU420 132 
#define  DRM_FORMAT_YVU422 131 
#define  DRM_FORMAT_YVU444 130 
 int /*<<< orphan*/  DRM_PLANE_HELPER_NO_SCALING ; 
#define  DRM_PLANE_TYPE_OVERLAY 129 
#define  DRM_PLANE_TYPE_PRIMARY 128 
 int EINVAL ; 
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  dev_warn (struct device*,char*,int) ; 
 struct drm_crtc_state* drm_atomic_get_existing_crtc_state (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int drm_atomic_helper_check_plane_state (struct drm_plane_state*,struct drm_crtc_state*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 unsigned long drm_plane_state_to_eba (struct drm_plane_state*,int) ; 
 unsigned long drm_plane_state_to_ubo (struct drm_plane_state*) ; 
 unsigned long drm_plane_state_to_vbo (struct drm_plane_state*) ; 
 int drm_rect_height (int /*<<< orphan*/ *) ; 
 scalar_t__ drm_rect_width (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ipu_plane_atomic_check(struct drm_plane *plane,
				  struct drm_plane_state *state)
{
	struct drm_plane_state *old_state = plane->state;
	struct drm_crtc_state *crtc_state;
	struct device *dev = plane->dev->dev;
	struct drm_framebuffer *fb = state->fb;
	struct drm_framebuffer *old_fb = old_state->fb;
	unsigned long eba, ubo, vbo, old_ubo, old_vbo, alpha_eba;
	bool can_position = (plane->type == DRM_PLANE_TYPE_OVERLAY);
	int ret;

	/* Ok to disable */
	if (!fb)
		return 0;

	if (!state->crtc)
		return -EINVAL;

	crtc_state =
		drm_atomic_get_existing_crtc_state(state->state, state->crtc);
	if (WARN_ON(!crtc_state))
		return -EINVAL;

	ret = drm_atomic_helper_check_plane_state(state, crtc_state,
						  DRM_PLANE_HELPER_NO_SCALING,
						  DRM_PLANE_HELPER_NO_SCALING,
						  can_position, true);
	if (ret)
		return ret;

	/* nothing to check when disabling or disabled */
	if (!crtc_state->enable)
		return 0;

	switch (plane->type) {
	case DRM_PLANE_TYPE_PRIMARY:
		/* full plane minimum width is 13 pixels */
		if (drm_rect_width(&state->dst) < 13)
			return -EINVAL;
		break;
	case DRM_PLANE_TYPE_OVERLAY:
		break;
	default:
		dev_warn(dev, "Unsupported plane type %d\n", plane->type);
		return -EINVAL;
	}

	if (drm_rect_height(&state->dst) < 2)
		return -EINVAL;

	/*
	 * We support resizing active plane or changing its format by
	 * forcing CRTC mode change in plane's ->atomic_check callback
	 * and disabling all affected active planes in CRTC's ->atomic_disable
	 * callback.  The planes will be reenabled in plane's ->atomic_update
	 * callback.
	 */
	if (old_fb &&
	    (drm_rect_width(&state->dst) != drm_rect_width(&old_state->dst) ||
	     drm_rect_height(&state->dst) != drm_rect_height(&old_state->dst) ||
	     fb->format != old_fb->format))
		crtc_state->mode_changed = true;

	eba = drm_plane_state_to_eba(state, 0);

	if (eba & 0x7)
		return -EINVAL;

	if (fb->pitches[0] < 1 || fb->pitches[0] > 16384)
		return -EINVAL;

	if (old_fb && fb->pitches[0] != old_fb->pitches[0])
		crtc_state->mode_changed = true;

	switch (fb->format->format) {
	case DRM_FORMAT_YUV420:
	case DRM_FORMAT_YVU420:
	case DRM_FORMAT_YUV422:
	case DRM_FORMAT_YVU422:
	case DRM_FORMAT_YUV444:
	case DRM_FORMAT_YVU444:
		/*
		 * Multiplanar formats have to meet the following restrictions:
		 * - The (up to) three plane addresses are EBA, EBA+UBO, EBA+VBO
		 * - EBA, UBO and VBO are a multiple of 8
		 * - UBO and VBO are unsigned and not larger than 0xfffff8
		 * - Only EBA may be changed while scanout is active
		 * - The strides of U and V planes must be identical.
		 */
		vbo = drm_plane_state_to_vbo(state);

		if (vbo & 0x7 || vbo > 0xfffff8)
			return -EINVAL;

		if (old_fb && (fb->format == old_fb->format)) {
			old_vbo = drm_plane_state_to_vbo(old_state);
			if (vbo != old_vbo)
				crtc_state->mode_changed = true;
		}

		if (fb->pitches[1] != fb->pitches[2])
			return -EINVAL;

		/* fall-through */
	case DRM_FORMAT_NV12:
	case DRM_FORMAT_NV16:
		ubo = drm_plane_state_to_ubo(state);

		if (ubo & 0x7 || ubo > 0xfffff8)
			return -EINVAL;

		if (old_fb && (fb->format == old_fb->format)) {
			old_ubo = drm_plane_state_to_ubo(old_state);
			if (ubo != old_ubo)
				crtc_state->mode_changed = true;
		}

		if (fb->pitches[1] < 1 || fb->pitches[1] > 16384)
			return -EINVAL;

		if (old_fb && old_fb->pitches[1] != fb->pitches[1])
			crtc_state->mode_changed = true;

		/*
		 * The x/y offsets must be even in case of horizontal/vertical
		 * chroma subsampling.
		 */
		if (((state->src.x1 >> 16) & (fb->format->hsub - 1)) ||
		    ((state->src.y1 >> 16) & (fb->format->vsub - 1)))
			return -EINVAL;
		break;
	case DRM_FORMAT_RGB565_A8:
	case DRM_FORMAT_BGR565_A8:
	case DRM_FORMAT_RGB888_A8:
	case DRM_FORMAT_BGR888_A8:
	case DRM_FORMAT_RGBX8888_A8:
	case DRM_FORMAT_BGRX8888_A8:
		alpha_eba = drm_plane_state_to_eba(state, 1);
		if (alpha_eba & 0x7)
			return -EINVAL;

		if (fb->pitches[1] < 1 || fb->pitches[1] > 16384)
			return -EINVAL;

		if (old_fb && old_fb->pitches[1] != fb->pitches[1])
			crtc_state->mode_changed = true;
		break;
	}

	return 0;
}