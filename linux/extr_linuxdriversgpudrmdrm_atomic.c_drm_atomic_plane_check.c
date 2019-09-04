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
struct drm_plane_state {scalar_t__ crtc_w; scalar_t__ crtc_x; scalar_t__ crtc_h; scalar_t__ crtc_y; unsigned int src_w; unsigned int src_x; unsigned int src_h; unsigned int src_y; int /*<<< orphan*/  state; TYPE_3__* fb; TYPE_5__* crtc; } ;
struct TYPE_9__ {int /*<<< orphan*/  id; } ;
struct drm_plane {int possible_crtcs; int /*<<< orphan*/  name; TYPE_4__ base; } ;
struct drm_format_name_buf {int dummy; } ;
typedef  scalar_t__ int32_t ;
struct TYPE_6__ {int /*<<< orphan*/  id; } ;
struct TYPE_10__ {int /*<<< orphan*/  name; TYPE_1__ base; } ;
struct TYPE_8__ {int width; int height; int /*<<< orphan*/  modifier; TYPE_2__* format; } ;
struct TYPE_7__ {int /*<<< orphan*/  format; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG_ATOMIC (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,...) ; 
 int EINVAL ; 
 int ENOSPC ; 
 int ERANGE ; 
 scalar_t__ INT_MAX ; 
 int drm_crtc_mask (TYPE_5__*) ; 
 int /*<<< orphan*/  drm_get_format_name (int /*<<< orphan*/ ,struct drm_format_name_buf*) ; 
 int drm_plane_check_pixel_format (struct drm_plane*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ plane_switching_crtc (int /*<<< orphan*/ ,struct drm_plane*,struct drm_plane_state*) ; 

__attribute__((used)) static int drm_atomic_plane_check(struct drm_plane *plane,
		struct drm_plane_state *state)
{
	unsigned int fb_width, fb_height;
	int ret;

	/* either *both* CRTC and FB must be set, or neither */
	if (state->crtc && !state->fb) {
		DRM_DEBUG_ATOMIC("[PLANE:%d:%s] CRTC set but no FB\n",
				 plane->base.id, plane->name);
		return -EINVAL;
	} else if (state->fb && !state->crtc) {
		DRM_DEBUG_ATOMIC("[PLANE:%d:%s] FB set but no CRTC\n",
				 plane->base.id, plane->name);
		return -EINVAL;
	}

	/* if disabled, we don't care about the rest of the state: */
	if (!state->crtc)
		return 0;

	/* Check whether this plane is usable on this CRTC */
	if (!(plane->possible_crtcs & drm_crtc_mask(state->crtc))) {
		DRM_DEBUG_ATOMIC("Invalid [CRTC:%d:%s] for [PLANE:%d:%s]\n",
				 state->crtc->base.id, state->crtc->name,
				 plane->base.id, plane->name);
		return -EINVAL;
	}

	/* Check whether this plane supports the fb pixel format. */
	ret = drm_plane_check_pixel_format(plane, state->fb->format->format,
					   state->fb->modifier);
	if (ret) {
		struct drm_format_name_buf format_name;
		DRM_DEBUG_ATOMIC("[PLANE:%d:%s] invalid pixel format %s, modifier 0x%llx\n",
				 plane->base.id, plane->name,
				 drm_get_format_name(state->fb->format->format,
						     &format_name),
				 state->fb->modifier);
		return ret;
	}

	/* Give drivers some help against integer overflows */
	if (state->crtc_w > INT_MAX ||
	    state->crtc_x > INT_MAX - (int32_t) state->crtc_w ||
	    state->crtc_h > INT_MAX ||
	    state->crtc_y > INT_MAX - (int32_t) state->crtc_h) {
		DRM_DEBUG_ATOMIC("[PLANE:%d:%s] invalid CRTC coordinates %ux%u+%d+%d\n",
				 plane->base.id, plane->name,
				 state->crtc_w, state->crtc_h,
				 state->crtc_x, state->crtc_y);
		return -ERANGE;
	}

	fb_width = state->fb->width << 16;
	fb_height = state->fb->height << 16;

	/* Make sure source coordinates are inside the fb. */
	if (state->src_w > fb_width ||
	    state->src_x > fb_width - state->src_w ||
	    state->src_h > fb_height ||
	    state->src_y > fb_height - state->src_h) {
		DRM_DEBUG_ATOMIC("[PLANE:%d:%s] invalid source coordinates "
				 "%u.%06ux%u.%06u+%u.%06u+%u.%06u (fb %ux%u)\n",
				 plane->base.id, plane->name,
				 state->src_w >> 16, ((state->src_w & 0xffff) * 15625) >> 10,
				 state->src_h >> 16, ((state->src_h & 0xffff) * 15625) >> 10,
				 state->src_x >> 16, ((state->src_x & 0xffff) * 15625) >> 10,
				 state->src_y >> 16, ((state->src_y & 0xffff) * 15625) >> 10,
				 state->fb->width, state->fb->height);
		return -ENOSPC;
	}

	if (plane_switching_crtc(state->state, plane, state)) {
		DRM_DEBUG_ATOMIC("[PLANE:%d:%s] switching CRTC directly\n",
				 plane->base.id, plane->name);
		return -EINVAL;
	}

	return 0;
}