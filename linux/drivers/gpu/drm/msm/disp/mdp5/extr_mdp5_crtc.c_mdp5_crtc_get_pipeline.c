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
struct mdp5_pipeline {int dummy; } ;
struct mdp5_crtc_state {struct mdp5_pipeline pipeline; } ;
struct drm_crtc {int /*<<< orphan*/  state; } ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 struct mdp5_pipeline* ERR_PTR (int /*<<< orphan*/ ) ; 
 scalar_t__ WARN_ON (int) ; 
 struct mdp5_crtc_state* to_mdp5_crtc_state (int /*<<< orphan*/ ) ; 

struct mdp5_pipeline *mdp5_crtc_get_pipeline(struct drm_crtc *crtc)
{
	struct mdp5_crtc_state *mdp5_cstate;

	if (WARN_ON(!crtc))
		return ERR_PTR(-EINVAL);

	mdp5_cstate = to_mdp5_crtc_state(crtc->state);

	return &mdp5_cstate->pipeline;
}