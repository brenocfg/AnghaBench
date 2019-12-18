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
typedef  int u32 ;
struct malidp_plane {TYPE_1__* layer; } ;
struct malidp_crtc_state {int scaled_planes_mask; } ;
struct drm_plane_state {int rotation; int src_h; int src_w; int crtc_w; int crtc_h; int /*<<< orphan*/  crtc; int /*<<< orphan*/  state; } ;
struct drm_crtc_state {int dummy; } ;
struct TYPE_2__ {int id; } ;

/* Variables and functions */
 int DE_GRAPHICS2 ; 
 int DE_SMART ; 
 int EINVAL ; 
 int /*<<< orphan*/  INT_MAX ; 
 int MALIDP_ROTATED_MASK ; 
 struct drm_crtc_state* drm_atomic_get_existing_crtc_state (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int drm_atomic_helper_check_plane_state (struct drm_plane_state*,struct drm_crtc_state*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 struct malidp_crtc_state* to_malidp_crtc_state (struct drm_crtc_state*) ; 

__attribute__((used)) static int malidp_se_check_scaling(struct malidp_plane *mp,
				   struct drm_plane_state *state)
{
	struct drm_crtc_state *crtc_state =
		drm_atomic_get_existing_crtc_state(state->state, state->crtc);
	struct malidp_crtc_state *mc;
	u32 src_w, src_h;
	int ret;

	if (!crtc_state)
		return -EINVAL;

	mc = to_malidp_crtc_state(crtc_state);

	ret = drm_atomic_helper_check_plane_state(state, crtc_state,
						  0, INT_MAX, true, true);
	if (ret)
		return ret;

	if (state->rotation & MALIDP_ROTATED_MASK) {
		src_w = state->src_h >> 16;
		src_h = state->src_w >> 16;
	} else {
		src_w = state->src_w >> 16;
		src_h = state->src_h >> 16;
	}

	if ((state->crtc_w == src_w) && (state->crtc_h == src_h)) {
		/* Scaling not necessary for this plane. */
		mc->scaled_planes_mask &= ~(mp->layer->id);
		return 0;
	}

	if (mp->layer->id & (DE_SMART | DE_GRAPHICS2))
		return -EINVAL;

	mc->scaled_planes_mask |= mp->layer->id;
	/* Defer scaling requirements calculation to the crtc check. */
	return 0;
}