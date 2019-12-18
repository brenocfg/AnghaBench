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
struct intel_crtc {int dummy; } ;
struct intel_atomic_state {int dummy; } ;
struct drm_connector_state {scalar_t__ crtc; } ;

/* Variables and functions */
 int /*<<< orphan*/  intel_atomic_get_new_crtc_state (struct intel_atomic_state*,struct intel_crtc*) ; 
 scalar_t__ needs_modeset (int /*<<< orphan*/ ) ; 
 struct intel_crtc* to_intel_crtc (scalar_t__) ; 

__attribute__((used)) static bool
intel_connector_needs_modeset(struct intel_atomic_state *state,
			      const struct drm_connector_state *old_conn_state,
			      const struct drm_connector_state *new_conn_state)
{
	struct intel_crtc *old_crtc = old_conn_state->crtc ?
				      to_intel_crtc(old_conn_state->crtc) : NULL;
	struct intel_crtc *new_crtc = new_conn_state->crtc ?
				      to_intel_crtc(new_conn_state->crtc) : NULL;

	return new_crtc != old_crtc ||
	       (new_crtc &&
		needs_modeset(intel_atomic_get_new_crtc_state(state, new_crtc)));
}