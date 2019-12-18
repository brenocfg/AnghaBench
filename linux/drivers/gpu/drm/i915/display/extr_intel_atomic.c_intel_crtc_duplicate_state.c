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
struct drm_crtc_state {int dummy; } ;
struct TYPE_2__ {int need_postvbl_update; } ;
struct intel_crtc_state {int update_pipe; int disable_lp_wm; int disable_cxsr; int update_wm_pre; int update_wm_post; int fb_changed; int fifo_changed; struct drm_crtc_state base; scalar_t__ update_planes; scalar_t__ fb_bits; TYPE_1__ wm; } ;
struct drm_crtc {int /*<<< orphan*/  state; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  __drm_atomic_helper_crtc_duplicate_state (struct drm_crtc*,struct drm_crtc_state*) ; 
 struct intel_crtc_state* kmemdup (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

struct drm_crtc_state *
intel_crtc_duplicate_state(struct drm_crtc *crtc)
{
	struct intel_crtc_state *crtc_state;

	crtc_state = kmemdup(crtc->state, sizeof(*crtc_state), GFP_KERNEL);
	if (!crtc_state)
		return NULL;

	__drm_atomic_helper_crtc_duplicate_state(crtc, &crtc_state->base);

	crtc_state->update_pipe = false;
	crtc_state->disable_lp_wm = false;
	crtc_state->disable_cxsr = false;
	crtc_state->update_wm_pre = false;
	crtc_state->update_wm_post = false;
	crtc_state->fb_changed = false;
	crtc_state->fifo_changed = false;
	crtc_state->wm.need_postvbl_update = false;
	crtc_state->fb_bits = 0;
	crtc_state->update_planes = 0;

	return &crtc_state->base;
}