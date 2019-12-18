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
struct TYPE_2__ {scalar_t__ colorspace; scalar_t__ picture_aspect_ratio; scalar_t__ content_type; scalar_t__ scaling_mode; int /*<<< orphan*/  hdr_output_metadata; } ;
struct intel_digital_connector_state {scalar_t__ force_audio; scalar_t__ broadcast_rgb; TYPE_1__ base; } ;
struct drm_crtc_state {int mode_changed; } ;
struct drm_connector_state {int /*<<< orphan*/  crtc; } ;
struct drm_connector {int dummy; } ;
struct drm_atomic_state {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  blob_equal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct drm_connector_state* drm_atomic_get_new_connector_state (struct drm_atomic_state*,struct drm_connector*) ; 
 struct drm_crtc_state* drm_atomic_get_new_crtc_state (struct drm_atomic_state*,int /*<<< orphan*/ ) ; 
 struct drm_connector_state* drm_atomic_get_old_connector_state (struct drm_atomic_state*,struct drm_connector*) ; 
 int /*<<< orphan*/  intel_hdcp_atomic_check (struct drm_connector*,struct drm_connector_state*,struct drm_connector_state*) ; 
 struct intel_digital_connector_state* to_intel_digital_connector_state (struct drm_connector_state*) ; 

int intel_digital_connector_atomic_check(struct drm_connector *conn,
					 struct drm_atomic_state *state)
{
	struct drm_connector_state *new_state =
		drm_atomic_get_new_connector_state(state, conn);
	struct intel_digital_connector_state *new_conn_state =
		to_intel_digital_connector_state(new_state);
	struct drm_connector_state *old_state =
		drm_atomic_get_old_connector_state(state, conn);
	struct intel_digital_connector_state *old_conn_state =
		to_intel_digital_connector_state(old_state);
	struct drm_crtc_state *crtc_state;

	intel_hdcp_atomic_check(conn, old_state, new_state);

	if (!new_state->crtc)
		return 0;

	crtc_state = drm_atomic_get_new_crtc_state(state, new_state->crtc);

	/*
	 * These properties are handled by fastset, and might not end
	 * up in a modeset.
	 */
	if (new_conn_state->force_audio != old_conn_state->force_audio ||
	    new_conn_state->broadcast_rgb != old_conn_state->broadcast_rgb ||
	    new_conn_state->base.colorspace != old_conn_state->base.colorspace ||
	    new_conn_state->base.picture_aspect_ratio != old_conn_state->base.picture_aspect_ratio ||
	    new_conn_state->base.content_type != old_conn_state->base.content_type ||
	    new_conn_state->base.scaling_mode != old_conn_state->base.scaling_mode ||
	    !blob_equal(new_conn_state->base.hdr_output_metadata,
			old_conn_state->base.hdr_output_metadata))
		crtc_state->mode_changed = true;

	return 0;
}