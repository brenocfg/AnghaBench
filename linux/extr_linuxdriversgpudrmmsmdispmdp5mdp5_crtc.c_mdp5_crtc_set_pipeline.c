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
struct mdp5_kms {int /*<<< orphan*/  base; } ;
struct mdp5_crtc_state {int /*<<< orphan*/  pipeline; int /*<<< orphan*/  ctl; } ;
struct drm_crtc {int /*<<< orphan*/  state; } ;

/* Variables and functions */
 struct mdp5_kms* get_kms (struct drm_crtc*) ; 
 int /*<<< orphan*/  mdp5_ctl_set_pipeline (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mdp_irq_update (int /*<<< orphan*/ *) ; 
 struct mdp5_crtc_state* to_mdp5_crtc_state (int /*<<< orphan*/ ) ; 

void mdp5_crtc_set_pipeline(struct drm_crtc *crtc)
{
	struct mdp5_crtc_state *mdp5_cstate = to_mdp5_crtc_state(crtc->state);
	struct mdp5_kms *mdp5_kms = get_kms(crtc);

	/* should this be done elsewhere ? */
	mdp_irq_update(&mdp5_kms->base);

	mdp5_ctl_set_pipeline(mdp5_cstate->ctl, &mdp5_cstate->pipeline);
}