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
struct vmw_crtc_state {struct drm_crtc_state base; } ;
struct drm_crtc {int /*<<< orphan*/  state; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  __drm_atomic_helper_crtc_duplicate_state (struct drm_crtc*,struct drm_crtc_state*) ; 
 struct vmw_crtc_state* kmemdup (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

struct drm_crtc_state *
vmw_du_crtc_duplicate_state(struct drm_crtc *crtc)
{
	struct drm_crtc_state *state;
	struct vmw_crtc_state *vcs;

	if (WARN_ON(!crtc->state))
		return NULL;

	vcs = kmemdup(crtc->state, sizeof(*vcs), GFP_KERNEL);

	if (!vcs)
		return NULL;

	state = &vcs->base;

	__drm_atomic_helper_crtc_duplicate_state(crtc, state);

	return state;
}