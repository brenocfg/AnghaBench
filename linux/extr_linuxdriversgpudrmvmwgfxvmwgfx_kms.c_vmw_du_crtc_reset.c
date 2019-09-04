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
struct vmw_crtc_state {TYPE_1__ base; } ;
struct drm_crtc {TYPE_1__* state; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_ERROR (char*) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  __drm_atomic_helper_crtc_destroy_state (TYPE_1__*) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 struct vmw_crtc_state* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vmw_crtc_state_to_vcs (TYPE_1__*) ; 

void vmw_du_crtc_reset(struct drm_crtc *crtc)
{
	struct vmw_crtc_state *vcs;


	if (crtc->state) {
		__drm_atomic_helper_crtc_destroy_state(crtc->state);

		kfree(vmw_crtc_state_to_vcs(crtc->state));
	}

	vcs = kzalloc(sizeof(*vcs), GFP_KERNEL);

	if (!vcs) {
		DRM_ERROR("Cannot allocate vmw_crtc_state\n");
		return;
	}

	crtc->state = &vcs->base;
	crtc->state->crtc = crtc;
}