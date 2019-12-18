#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct vop_win_data {TYPE_1__* phy; } ;
struct vop_win {struct vop_win_data* data; } ;
struct drm_plane_state {TYPE_4__* crtc; scalar_t__ state; } ;
struct drm_plane {TYPE_3__* state; TYPE_2__* crtc; } ;
struct drm_crtc_state {int dummy; } ;
struct TYPE_8__ {struct drm_plane* cursor; } ;
struct TYPE_7__ {int /*<<< orphan*/  fb; } ;
struct TYPE_6__ {struct drm_crtc_state* state; } ;
struct TYPE_5__ {scalar_t__ scl; } ;

/* Variables and functions */
 int DRM_PLANE_HELPER_NO_SCALING ; 
 int EINVAL ; 
 int FRAC_16_16 (int,int) ; 
 struct drm_crtc_state* drm_atomic_get_existing_crtc_state (scalar_t__,TYPE_4__*) ; 
 int drm_atomic_helper_check_plane_state (TYPE_3__*,struct drm_crtc_state*,int,int,int,int) ; 
 struct vop_win* to_vop_win (struct drm_plane*) ; 

__attribute__((used)) static int vop_plane_atomic_async_check(struct drm_plane *plane,
					struct drm_plane_state *state)
{
	struct vop_win *vop_win = to_vop_win(plane);
	const struct vop_win_data *win = vop_win->data;
	int min_scale = win->phy->scl ? FRAC_16_16(1, 8) :
					DRM_PLANE_HELPER_NO_SCALING;
	int max_scale = win->phy->scl ? FRAC_16_16(8, 1) :
					DRM_PLANE_HELPER_NO_SCALING;
	struct drm_crtc_state *crtc_state;

	if (plane != state->crtc->cursor)
		return -EINVAL;

	if (!plane->state)
		return -EINVAL;

	if (!plane->state->fb)
		return -EINVAL;

	if (state->state)
		crtc_state = drm_atomic_get_existing_crtc_state(state->state,
								state->crtc);
	else /* Special case for asynchronous cursor updates. */
		crtc_state = plane->crtc->state;

	return drm_atomic_helper_check_plane_state(plane->state, crtc_state,
						   min_scale, max_scale,
						   true, true);
}