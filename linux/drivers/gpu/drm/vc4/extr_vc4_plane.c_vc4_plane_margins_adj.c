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
struct vc4_plane_state {unsigned int crtc_x; unsigned int crtc_y; unsigned int crtc_w; unsigned int crtc_h; } ;
struct drm_plane_state {int /*<<< orphan*/  crtc; int /*<<< orphan*/  state; } ;
struct TYPE_2__ {unsigned int hdisplay; unsigned int vdisplay; } ;
struct drm_crtc_state {TYPE_1__ mode; } ;

/* Variables and functions */
 void* DIV_ROUND_CLOSEST (unsigned int,unsigned int) ; 
 int EINVAL ; 
 struct drm_crtc_state* drm_atomic_get_new_crtc_state (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct vc4_plane_state* to_vc4_plane_state (struct drm_plane_state*) ; 
 int /*<<< orphan*/  vc4_crtc_get_margins (struct drm_crtc_state*,unsigned int*,unsigned int*,unsigned int*,unsigned int*) ; 

__attribute__((used)) static int vc4_plane_margins_adj(struct drm_plane_state *pstate)
{
	struct vc4_plane_state *vc4_pstate = to_vc4_plane_state(pstate);
	unsigned int left, right, top, bottom, adjhdisplay, adjvdisplay;
	struct drm_crtc_state *crtc_state;

	crtc_state = drm_atomic_get_new_crtc_state(pstate->state,
						   pstate->crtc);

	vc4_crtc_get_margins(crtc_state, &left, &right, &top, &bottom);
	if (!left && !right && !top && !bottom)
		return 0;

	if (left + right >= crtc_state->mode.hdisplay ||
	    top + bottom >= crtc_state->mode.vdisplay)
		return -EINVAL;

	adjhdisplay = crtc_state->mode.hdisplay - (left + right);
	vc4_pstate->crtc_x = DIV_ROUND_CLOSEST(vc4_pstate->crtc_x *
					       adjhdisplay,
					       crtc_state->mode.hdisplay);
	vc4_pstate->crtc_x += left;
	if (vc4_pstate->crtc_x > crtc_state->mode.hdisplay - left)
		vc4_pstate->crtc_x = crtc_state->mode.hdisplay - left;

	adjvdisplay = crtc_state->mode.vdisplay - (top + bottom);
	vc4_pstate->crtc_y = DIV_ROUND_CLOSEST(vc4_pstate->crtc_y *
					       adjvdisplay,
					       crtc_state->mode.vdisplay);
	vc4_pstate->crtc_y += top;
	if (vc4_pstate->crtc_y > crtc_state->mode.vdisplay - top)
		vc4_pstate->crtc_y = crtc_state->mode.vdisplay - top;

	vc4_pstate->crtc_w = DIV_ROUND_CLOSEST(vc4_pstate->crtc_w *
					       adjhdisplay,
					       crtc_state->mode.hdisplay);
	vc4_pstate->crtc_h = DIV_ROUND_CLOSEST(vc4_pstate->crtc_h *
					       adjvdisplay,
					       crtc_state->mode.vdisplay);

	if (!vc4_pstate->crtc_w || !vc4_pstate->crtc_h)
		return -EINVAL;

	return 0;
}