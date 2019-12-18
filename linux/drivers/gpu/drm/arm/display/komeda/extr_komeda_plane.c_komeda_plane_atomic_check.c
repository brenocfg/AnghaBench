#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct komeda_plane_state {int dummy; } ;
struct komeda_plane {struct komeda_layer* layer; } ;
struct komeda_layer {int dummy; } ;
struct komeda_data_flow_cfg {scalar_t__ en_split; } ;
struct komeda_crtc_state {int dummy; } ;
struct drm_plane_state {int /*<<< orphan*/  crtc; int /*<<< orphan*/  state; int /*<<< orphan*/  fb; } ;
struct drm_plane {int dummy; } ;
struct drm_crtc_state {int /*<<< orphan*/  active; int /*<<< orphan*/  enable; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG_ATOMIC (char*) ; 
 int EINVAL ; 
 scalar_t__ IS_ERR (struct drm_crtc_state*) ; 
 struct drm_crtc_state* drm_atomic_get_crtc_state (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int komeda_build_layer_data_flow (struct komeda_layer*,struct komeda_plane_state*,struct komeda_crtc_state*,struct komeda_data_flow_cfg*) ; 
 int komeda_build_layer_split_data_flow (struct komeda_layer*,struct komeda_plane_state*,struct komeda_crtc_state*,struct komeda_data_flow_cfg*) ; 
 int komeda_plane_init_data_flow (struct drm_plane_state*,struct komeda_crtc_state*,struct komeda_data_flow_cfg*) ; 
 struct komeda_crtc_state* to_kcrtc_st (struct drm_crtc_state*) ; 
 struct komeda_plane* to_kplane (struct drm_plane*) ; 
 struct komeda_plane_state* to_kplane_st (struct drm_plane_state*) ; 

__attribute__((used)) static int
komeda_plane_atomic_check(struct drm_plane *plane,
			  struct drm_plane_state *state)
{
	struct komeda_plane *kplane = to_kplane(plane);
	struct komeda_plane_state *kplane_st = to_kplane_st(state);
	struct komeda_layer *layer = kplane->layer;
	struct drm_crtc_state *crtc_st;
	struct komeda_crtc_state *kcrtc_st;
	struct komeda_data_flow_cfg dflow;
	int err;

	if (!state->crtc || !state->fb)
		return 0;

	crtc_st = drm_atomic_get_crtc_state(state->state, state->crtc);
	if (IS_ERR(crtc_st) || !crtc_st->enable) {
		DRM_DEBUG_ATOMIC("Cannot update plane on a disabled CRTC.\n");
		return -EINVAL;
	}

	/* crtc is inactive, skip the resource assignment */
	if (!crtc_st->active)
		return 0;

	kcrtc_st = to_kcrtc_st(crtc_st);

	err = komeda_plane_init_data_flow(state, kcrtc_st, &dflow);
	if (err)
		return err;

	if (dflow.en_split)
		err = komeda_build_layer_split_data_flow(layer,
				kplane_st, kcrtc_st, &dflow);
	else
		err = komeda_build_layer_data_flow(layer,
				kplane_st, kcrtc_st, &dflow);

	return err;
}