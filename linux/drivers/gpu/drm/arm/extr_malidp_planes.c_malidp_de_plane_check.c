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
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
typedef  scalar_t__ u16 ;
struct malidp_plane_state {scalar_t__ format; int n_planes; int rotmem_size; } ;
struct malidp_plane {TYPE_3__* hwdev; TYPE_1__* layer; } ;
struct drm_plane_state {int rotation; scalar_t__ pixel_blend_mode; int src_x; int src_y; scalar_t__ crtc_w; scalar_t__ crtc_h; scalar_t__ alpha; struct drm_framebuffer* fb; int /*<<< orphan*/  crtc; } ;
struct drm_plane {int dummy; } ;
struct drm_framebuffer {int* pitches; unsigned int width; unsigned int height; TYPE_5__* format; scalar_t__ modifier; } ;
struct TYPE_10__ {scalar_t__ format; int num_planes; scalar_t__ has_alpha; } ;
struct TYPE_9__ {scalar_t__ max_line_size; scalar_t__ min_line_size; TYPE_2__* hw; } ;
struct TYPE_8__ {int features; int (* rotmem_required ) (TYPE_3__*,scalar_t__,scalar_t__,scalar_t__,int) ;int /*<<< orphan*/  map; } ;
struct TYPE_7__ {scalar_t__ id; scalar_t__ rot; } ;

/* Variables and functions */
 scalar_t__ DE_SMART ; 
 scalar_t__ DRM_BLEND_ALPHA_OPAQUE ; 
 int /*<<< orphan*/  DRM_DEBUG_KMS (char*,...) ; 
 int /*<<< orphan*/  DRM_ERROR (char*) ; 
 scalar_t__ DRM_FORMAT_BGR888 ; 
 scalar_t__ DRM_FORMAT_RGB888 ; 
 scalar_t__ DRM_MODE_BLEND_PIXEL_NONE ; 
 int DRM_MODE_ROTATE_0 ; 
 int EINVAL ; 
 int MALIDP_DEVICE_LV_HAS_3_STRIDES ; 
 scalar_t__ MALIDP_INVALID_FORMAT_ID ; 
 int MALIDP_ROTATED_MASK ; 
 scalar_t__ ROTATE_COMPRESSED ; 
 scalar_t__ ROTATE_NONE ; 
 int drm_format_info_block_height (TYPE_5__*,int) ; 
 unsigned int drm_format_info_block_width (TYPE_5__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  malidp_de_prefetch_settings (struct malidp_plane*,struct malidp_plane_state*) ; 
 scalar_t__ malidp_hw_get_format_id (int /*<<< orphan*/ *,scalar_t__,scalar_t__,int) ; 
 int malidp_hw_get_pitch_align (TYPE_3__*,int) ; 
 int malidp_se_check_scaling (struct malidp_plane*,struct drm_plane_state*) ; 
 int stub1 (TYPE_3__*,scalar_t__,scalar_t__,scalar_t__,int) ; 
 struct malidp_plane* to_malidp_plane (struct drm_plane*) ; 
 struct malidp_plane_state* to_malidp_plane_state (struct drm_plane_state*) ; 

__attribute__((used)) static int malidp_de_plane_check(struct drm_plane *plane,
				 struct drm_plane_state *state)
{
	struct malidp_plane *mp = to_malidp_plane(plane);
	struct malidp_plane_state *ms = to_malidp_plane_state(state);
	bool rotated = state->rotation & MALIDP_ROTATED_MASK;
	struct drm_framebuffer *fb;
	u16 pixel_alpha = state->pixel_blend_mode;
	int i, ret;
	unsigned int block_w, block_h;

	if (!state->crtc || !state->fb)
		return 0;

	fb = state->fb;

	ms->format = malidp_hw_get_format_id(&mp->hwdev->hw->map,
					     mp->layer->id, fb->format->format,
					     !!fb->modifier);
	if (ms->format == MALIDP_INVALID_FORMAT_ID)
		return -EINVAL;

	ms->n_planes = fb->format->num_planes;
	for (i = 0; i < ms->n_planes; i++) {
		u8 alignment = malidp_hw_get_pitch_align(mp->hwdev, rotated);

		if (((fb->pitches[i] * drm_format_info_block_height(fb->format, i))
				& (alignment - 1)) && !(fb->modifier)) {
			DRM_DEBUG_KMS("Invalid pitch %u for plane %d\n",
				      fb->pitches[i], i);
			return -EINVAL;
		}
	}

	block_w = drm_format_info_block_width(fb->format, 0);
	block_h = drm_format_info_block_height(fb->format, 0);
	if (fb->width % block_w || fb->height % block_h) {
		DRM_DEBUG_KMS("Buffer width/height needs to be a multiple of tile sizes");
		return -EINVAL;
	}
	if ((state->src_x >> 16) % block_w || (state->src_y >> 16) % block_h) {
		DRM_DEBUG_KMS("Plane src_x/src_y needs to be a multiple of tile sizes");
		return -EINVAL;
	}

	if ((state->crtc_w > mp->hwdev->max_line_size) ||
	    (state->crtc_h > mp->hwdev->max_line_size) ||
	    (state->crtc_w < mp->hwdev->min_line_size) ||
	    (state->crtc_h < mp->hwdev->min_line_size))
		return -EINVAL;

	/*
	 * DP550/650 video layers can accept 3 plane formats only if
	 * fb->pitches[1] == fb->pitches[2] since they don't have a
	 * third plane stride register.
	 */
	if (ms->n_planes == 3 &&
	    !(mp->hwdev->hw->features & MALIDP_DEVICE_LV_HAS_3_STRIDES) &&
	    (state->fb->pitches[1] != state->fb->pitches[2]))
		return -EINVAL;

	ret = malidp_se_check_scaling(mp, state);
	if (ret)
		return ret;

	/* validate the rotation constraints for each layer */
	if (state->rotation != DRM_MODE_ROTATE_0) {
		if (mp->layer->rot == ROTATE_NONE)
			return -EINVAL;
		if ((mp->layer->rot == ROTATE_COMPRESSED) && !(fb->modifier))
			return -EINVAL;
		/*
		 * packed RGB888 / BGR888 can't be rotated or flipped
		 * unless they are stored in a compressed way
		 */
		if ((fb->format->format == DRM_FORMAT_RGB888 ||
		     fb->format->format == DRM_FORMAT_BGR888) && !(fb->modifier))
			return -EINVAL;
	}

	/* SMART layer does not support AFBC */
	if (mp->layer->id == DE_SMART && fb->modifier) {
		DRM_ERROR("AFBC framebuffer not supported in SMART layer");
		return -EINVAL;
	}

	ms->rotmem_size = 0;
	if (state->rotation & MALIDP_ROTATED_MASK) {
		int val;

		val = mp->hwdev->hw->rotmem_required(mp->hwdev, state->crtc_w,
						     state->crtc_h,
						     fb->format->format,
						     !!(fb->modifier));
		if (val < 0)
			return val;

		ms->rotmem_size = val;
	}

	/* HW can't support plane + pixel blending */
	if ((state->alpha != DRM_BLEND_ALPHA_OPAQUE) &&
	    (pixel_alpha != DRM_MODE_BLEND_PIXEL_NONE) &&
	    fb->format->has_alpha)
		return -EINVAL;

	malidp_de_prefetch_settings(mp, ms);

	return 0;
}