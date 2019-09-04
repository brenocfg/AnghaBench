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
struct drm_crtc_state {struct drm_crtc* crtc; } ;
struct drm_crtc {struct drm_crtc_state* state; TYPE_1__* funcs; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* atomic_destroy_state ) (struct drm_crtc*,struct drm_crtc_state*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (struct drm_crtc*,struct drm_crtc_state*) ; 

__attribute__((used)) static void
__drm_atomic_helper_crtc_reset(struct drm_crtc *crtc,
			       struct drm_crtc_state *state)
{
	if (crtc->state)
		crtc->funcs->atomic_destroy_state(crtc, crtc->state);
	crtc->state = state;
	crtc->state->crtc = crtc;
}