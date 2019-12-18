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
struct intel_sdvo_connector_state {int /*<<< orphan*/  tv; } ;
struct drm_crtc_state {int connectors_changed; } ;
struct drm_connector_state {scalar_t__ crtc; int /*<<< orphan*/  tv; } ;
struct drm_connector {int dummy; } ;
struct drm_atomic_state {int dummy; } ;

/* Variables and functions */
 struct drm_connector_state* drm_atomic_get_new_connector_state (struct drm_atomic_state*,struct drm_connector*) ; 
 struct drm_crtc_state* drm_atomic_get_new_crtc_state (struct drm_atomic_state*,scalar_t__) ; 
 struct drm_connector_state* drm_atomic_get_old_connector_state (struct drm_atomic_state*,struct drm_connector*) ; 
 int intel_digital_connector_atomic_check (struct drm_connector*,struct drm_atomic_state*) ; 
 scalar_t__ memcmp (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 struct intel_sdvo_connector_state* to_intel_sdvo_connector_state (struct drm_connector_state*) ; 

__attribute__((used)) static int intel_sdvo_atomic_check(struct drm_connector *conn,
				   struct drm_atomic_state *state)
{
	struct drm_connector_state *new_conn_state =
		drm_atomic_get_new_connector_state(state, conn);
	struct drm_connector_state *old_conn_state =
		drm_atomic_get_old_connector_state(state, conn);
	struct intel_sdvo_connector_state *old_state =
		to_intel_sdvo_connector_state(old_conn_state);
	struct intel_sdvo_connector_state *new_state =
		to_intel_sdvo_connector_state(new_conn_state);

	if (new_conn_state->crtc &&
	    (memcmp(&old_state->tv, &new_state->tv, sizeof(old_state->tv)) ||
	     memcmp(&old_conn_state->tv, &new_conn_state->tv, sizeof(old_conn_state->tv)))) {
		struct drm_crtc_state *crtc_state =
			drm_atomic_get_new_crtc_state(state,
						      new_conn_state->crtc);

		crtc_state->connectors_changed = true;
	}

	return intel_digital_connector_atomic_check(conn, state);
}