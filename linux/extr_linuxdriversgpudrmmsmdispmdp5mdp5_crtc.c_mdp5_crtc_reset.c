#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {struct drm_crtc* crtc; } ;
struct mdp5_crtc_state {TYPE_1__ base; } ;
struct drm_crtc {TYPE_1__* state; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  __drm_atomic_helper_crtc_destroy_state (TYPE_1__*) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 struct mdp5_crtc_state* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  to_mdp5_crtc_state (TYPE_1__*) ; 

__attribute__((used)) static void mdp5_crtc_reset(struct drm_crtc *crtc)
{
	struct mdp5_crtc_state *mdp5_cstate;

	if (crtc->state) {
		__drm_atomic_helper_crtc_destroy_state(crtc->state);
		kfree(to_mdp5_crtc_state(crtc->state));
	}

	mdp5_cstate = kzalloc(sizeof(*mdp5_cstate), GFP_KERNEL);

	if (mdp5_cstate) {
		mdp5_cstate->base.crtc = crtc;
		crtc->state = &mdp5_cstate->base;
	}
}