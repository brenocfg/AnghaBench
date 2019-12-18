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
typedef  int /*<<< orphan*/  u32 ;
struct mdp5_pipeline {struct mdp5_hw_mixer* mixer; struct mdp5_interface* intf; struct mdp5_hw_mixer* r_mixer; } ;
struct mdp5_interface {scalar_t__ type; scalar_t__ mode; int /*<<< orphan*/  num; } ;
struct mdp5_hw_mixer {int dummy; } ;
struct mdp5_crtc_state {int cmd_mode; scalar_t__ pp_done_irqmask; int /*<<< orphan*/  vblank_irqmask; int /*<<< orphan*/  err_irqmask; struct mdp5_pipeline pipeline; } ;
struct drm_crtc_state {int /*<<< orphan*/  state; } ;
struct drm_crtc {int dummy; } ;

/* Variables and functions */
 scalar_t__ INTF_DSI ; 
 scalar_t__ MDP5_INTF_DSI_MODE_COMMAND ; 
 int /*<<< orphan*/  MDP_LM_CAP_DISPLAY ; 
 int /*<<< orphan*/  MDP_LM_CAP_PAIR ; 
 int /*<<< orphan*/  intf2err (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  intf2vblank (struct mdp5_hw_mixer*,struct mdp5_interface*) ; 
 scalar_t__ lm2ppdone (struct mdp5_hw_mixer*) ; 
 int mdp5_mixer_assign (int /*<<< orphan*/ ,struct drm_crtc*,int /*<<< orphan*/ ,struct mdp5_hw_mixer**,struct mdp5_hw_mixer**) ; 
 int /*<<< orphan*/  mdp5_mixer_release (int /*<<< orphan*/ ,struct mdp5_hw_mixer*) ; 
 struct mdp5_crtc_state* to_mdp5_crtc_state (struct drm_crtc_state*) ; 

int mdp5_crtc_setup_pipeline(struct drm_crtc *crtc,
			     struct drm_crtc_state *new_crtc_state,
			     bool need_right_mixer)
{
	struct mdp5_crtc_state *mdp5_cstate =
			to_mdp5_crtc_state(new_crtc_state);
	struct mdp5_pipeline *pipeline = &mdp5_cstate->pipeline;
	struct mdp5_interface *intf;
	bool new_mixer = false;

	new_mixer = !pipeline->mixer;

	if ((need_right_mixer && !pipeline->r_mixer) ||
	    (!need_right_mixer && pipeline->r_mixer))
		new_mixer = true;

	if (new_mixer) {
		struct mdp5_hw_mixer *old_mixer = pipeline->mixer;
		struct mdp5_hw_mixer *old_r_mixer = pipeline->r_mixer;
		u32 caps;
		int ret;

		caps = MDP_LM_CAP_DISPLAY;
		if (need_right_mixer)
			caps |= MDP_LM_CAP_PAIR;

		ret = mdp5_mixer_assign(new_crtc_state->state, crtc, caps,
					&pipeline->mixer, need_right_mixer ?
					&pipeline->r_mixer : NULL);
		if (ret)
			return ret;

		mdp5_mixer_release(new_crtc_state->state, old_mixer);
		if (old_r_mixer) {
			mdp5_mixer_release(new_crtc_state->state, old_r_mixer);
			if (!need_right_mixer)
				pipeline->r_mixer = NULL;
		}
	}

	/*
	 * these should have been already set up in the encoder's atomic
	 * check (called by drm_atomic_helper_check_modeset)
	 */
	intf = pipeline->intf;

	mdp5_cstate->err_irqmask = intf2err(intf->num);
	mdp5_cstate->vblank_irqmask = intf2vblank(pipeline->mixer, intf);

	if ((intf->type == INTF_DSI) &&
	    (intf->mode == MDP5_INTF_DSI_MODE_COMMAND)) {
		mdp5_cstate->pp_done_irqmask = lm2ppdone(pipeline->mixer);
		mdp5_cstate->cmd_mode = true;
	} else {
		mdp5_cstate->pp_done_irqmask = 0;
		mdp5_cstate->cmd_mode = false;
	}

	return 0;
}