#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int y1; int y2; int x1; } ;
struct drm_plane_state {int visible; TYPE_2__ dst; TYPE_2__ src; scalar_t__ state; struct drm_crtc* crtc; int /*<<< orphan*/  fb; } ;
struct drm_plane {int dummy; } ;
struct TYPE_4__ {int flags; } ;
struct drm_crtc_state {TYPE_1__ adjusted_mode; } ;
struct drm_crtc {struct drm_crtc_state* state; } ;
struct armada_plane_state {int src_hw; int dst_yx; int dst_hw; int interlace; int /*<<< orphan*/  pitches; int /*<<< orphan*/  addrs; } ;

/* Variables and functions */
 int DRM_MODE_FLAG_INTERLACE ; 
 int EINVAL ; 
 int /*<<< orphan*/  INT_MAX ; 
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  armada_drm_plane_calc (struct drm_plane_state*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 struct drm_crtc_state* drm_atomic_get_existing_crtc_state (scalar_t__,struct drm_crtc*) ; 
 int drm_atomic_helper_check_plane_state (struct drm_plane_state*,struct drm_crtc_state*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int drm_rect_height (TYPE_2__*) ; 
 int drm_rect_width (TYPE_2__*) ; 
 struct armada_plane_state* to_armada_plane_state (struct drm_plane_state*) ; 

int armada_drm_plane_atomic_check(struct drm_plane *plane,
	struct drm_plane_state *state)
{
	struct armada_plane_state *st = to_armada_plane_state(state);
	struct drm_crtc *crtc = state->crtc;
	struct drm_crtc_state *crtc_state;
	bool interlace;
	int ret;

	if (!state->fb || WARN_ON(!state->crtc)) {
		state->visible = false;
		return 0;
	}

	if (state->state)
		crtc_state = drm_atomic_get_existing_crtc_state(state->state, crtc);
	else
		crtc_state = crtc->state;

	ret = drm_atomic_helper_check_plane_state(state, crtc_state, 0,
						  INT_MAX, true, false);
	if (ret)
		return ret;

	interlace = crtc_state->adjusted_mode.flags & DRM_MODE_FLAG_INTERLACE;
	if (interlace) {
		if ((state->dst.y1 | state->dst.y2) & 1)
			return -EINVAL;
		st->src_hw = drm_rect_height(&state->src) >> 17;
		st->dst_yx = state->dst.y1 >> 1;
		st->dst_hw = drm_rect_height(&state->dst) >> 1;
	} else {
		st->src_hw = drm_rect_height(&state->src) >> 16;
		st->dst_yx = state->dst.y1;
		st->dst_hw = drm_rect_height(&state->dst);
	}

	st->src_hw <<= 16;
	st->src_hw |= drm_rect_width(&state->src) >> 16;
	st->dst_yx <<= 16;
	st->dst_yx |= state->dst.x1 & 0x0000ffff;
	st->dst_hw <<= 16;
	st->dst_hw |= drm_rect_width(&state->dst) & 0x0000ffff;

	armada_drm_plane_calc(state, st->addrs, st->pitches, interlace);
	st->interlace = interlace;

	return 0;
}