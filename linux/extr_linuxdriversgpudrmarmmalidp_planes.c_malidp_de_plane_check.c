#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct malidp_plane_state {scalar_t__ format; int n_planes; int rotmem_size; } ;
struct malidp_plane {TYPE_4__* hwdev; TYPE_1__* layer; } ;
struct drm_plane_state {int rotation; scalar_t__ crtc_w; scalar_t__ crtc_h; struct drm_framebuffer* fb; int /*<<< orphan*/  crtc; } ;
struct drm_plane {int dummy; } ;
struct drm_framebuffer {int* pitches; TYPE_3__* format; } ;
struct TYPE_9__ {scalar_t__ max_line_size; scalar_t__ min_line_size; TYPE_2__* hw; } ;
struct TYPE_8__ {scalar_t__ format; int num_planes; } ;
struct TYPE_7__ {int features; int (* rotmem_required ) (TYPE_4__*,scalar_t__,scalar_t__,scalar_t__) ;int /*<<< orphan*/  map; } ;
struct TYPE_6__ {int /*<<< orphan*/  id; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG_KMS (char*,int,int) ; 
 scalar_t__ DRM_FORMAT_BGR888 ; 
 scalar_t__ DRM_FORMAT_RGB888 ; 
 int DRM_MODE_ROTATE_0 ; 
 int EINVAL ; 
 int MALIDP_DEVICE_LV_HAS_3_STRIDES ; 
 scalar_t__ MALIDP_INVALID_FORMAT_ID ; 
 int MALIDP_ROTATED_MASK ; 
 scalar_t__ malidp_hw_get_format_id (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__) ; 
 int malidp_hw_get_pitch_align (TYPE_4__*,int) ; 
 int malidp_se_check_scaling (struct malidp_plane*,struct drm_plane_state*) ; 
 int stub1 (TYPE_4__*,scalar_t__,scalar_t__,scalar_t__) ; 
 struct malidp_plane* to_malidp_plane (struct drm_plane*) ; 
 struct malidp_plane_state* to_malidp_plane_state (struct drm_plane_state*) ; 

__attribute__((used)) static int malidp_de_plane_check(struct drm_plane *plane,
				 struct drm_plane_state *state)
{
	struct malidp_plane *mp = to_malidp_plane(plane);
	struct malidp_plane_state *ms = to_malidp_plane_state(state);
	bool rotated = state->rotation & MALIDP_ROTATED_MASK;
	struct drm_framebuffer *fb;
	int i, ret;

	if (!state->crtc || !state->fb)
		return 0;

	fb = state->fb;

	ms->format = malidp_hw_get_format_id(&mp->hwdev->hw->map,
					     mp->layer->id,
					     fb->format->format);
	if (ms->format == MALIDP_INVALID_FORMAT_ID)
		return -EINVAL;

	ms->n_planes = fb->format->num_planes;
	for (i = 0; i < ms->n_planes; i++) {
		u8 alignment = malidp_hw_get_pitch_align(mp->hwdev, rotated);
		if (fb->pitches[i] & (alignment - 1)) {
			DRM_DEBUG_KMS("Invalid pitch %u for plane %d\n",
				      fb->pitches[i], i);
			return -EINVAL;
		}
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

	/* packed RGB888 / BGR888 can't be rotated or flipped */
	if (state->rotation != DRM_MODE_ROTATE_0 &&
	    (fb->format->format == DRM_FORMAT_RGB888 ||
	     fb->format->format == DRM_FORMAT_BGR888))
		return -EINVAL;

	ms->rotmem_size = 0;
	if (state->rotation & MALIDP_ROTATED_MASK) {
		int val;

		val = mp->hwdev->hw->rotmem_required(mp->hwdev, state->crtc_w,
						     state->crtc_h,
						     fb->format->format);
		if (val < 0)
			return val;

		ms->rotmem_size = val;
	}

	return 0;
}