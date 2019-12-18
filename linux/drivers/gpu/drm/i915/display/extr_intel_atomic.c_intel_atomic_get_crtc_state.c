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
struct intel_crtc_state {int dummy; } ;
struct intel_crtc {int /*<<< orphan*/  base; } ;
struct drm_crtc_state {int dummy; } ;
struct drm_atomic_state {int dummy; } ;

/* Variables and functions */
 struct intel_crtc_state* ERR_CAST (struct drm_crtc_state*) ; 
 scalar_t__ IS_ERR (struct drm_crtc_state*) ; 
 struct drm_crtc_state* drm_atomic_get_crtc_state (struct drm_atomic_state*,int /*<<< orphan*/ *) ; 
 struct intel_crtc_state* to_intel_crtc_state (struct drm_crtc_state*) ; 

struct intel_crtc_state *
intel_atomic_get_crtc_state(struct drm_atomic_state *state,
			    struct intel_crtc *crtc)
{
	struct drm_crtc_state *crtc_state;
	crtc_state = drm_atomic_get_crtc_state(state, &crtc->base);
	if (IS_ERR(crtc_state))
		return ERR_CAST(crtc_state);

	return to_intel_crtc_state(crtc_state);
}