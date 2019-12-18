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
struct drm_crtc_state {int dummy; } ;
struct mdp5_crtc_state {struct drm_crtc_state base; } ;
struct drm_crtc {int /*<<< orphan*/  state; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  __drm_atomic_helper_crtc_duplicate_state (struct drm_crtc*,struct drm_crtc_state*) ; 
 struct mdp5_crtc_state* kmemdup (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  to_mdp5_crtc_state (int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct drm_crtc_state *
mdp5_crtc_duplicate_state(struct drm_crtc *crtc)
{
	struct mdp5_crtc_state *mdp5_cstate;

	if (WARN_ON(!crtc->state))
		return NULL;

	mdp5_cstate = kmemdup(to_mdp5_crtc_state(crtc->state),
			      sizeof(*mdp5_cstate), GFP_KERNEL);
	if (!mdp5_cstate)
		return NULL;

	__drm_atomic_helper_crtc_duplicate_state(crtc, &mdp5_cstate->base);

	return &mdp5_cstate->base;
}