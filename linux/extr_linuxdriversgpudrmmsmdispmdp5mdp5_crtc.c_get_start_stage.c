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
struct TYPE_2__ {scalar_t__ r_mixer; } ;
struct mdp5_crtc_state {TYPE_1__ pipeline; } ;
struct drm_plane_state {int dummy; } ;
struct drm_crtc_state {int dummy; } ;
struct drm_crtc {int dummy; } ;
typedef  enum mdp_mixer_stage_id { ____Placeholder_mdp_mixer_stage_id } mdp_mixer_stage_id ;

/* Variables and functions */
 int STAGE0 ; 
 int STAGE_BASE ; 
 int /*<<< orphan*/  is_fullscreen (struct drm_crtc_state*,struct drm_plane_state*) ; 
 struct mdp5_crtc_state* to_mdp5_crtc_state (struct drm_crtc_state*) ; 

__attribute__((used)) static enum mdp_mixer_stage_id get_start_stage(struct drm_crtc *crtc,
					struct drm_crtc_state *new_crtc_state,
					struct drm_plane_state *bpstate)
{
	struct mdp5_crtc_state *mdp5_cstate =
			to_mdp5_crtc_state(new_crtc_state);

	/*
	 * if we're in source split mode, it's mandatory to have
	 * border out on the base stage
	 */
	if (mdp5_cstate->pipeline.r_mixer)
		return STAGE0;

	/* if the bottom-most layer is not fullscreen, we need to use
	 * it for solid-color:
	 */
	if (!is_fullscreen(new_crtc_state, bpstate))
		return STAGE0;

	return STAGE_BASE;
}