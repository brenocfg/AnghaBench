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
struct drm_crtc_state {int mode_changed; } ;
struct drm_crtc {int dummy; } ;
struct drm_connector_state {int /*<<< orphan*/  hdr_output_metadata; struct drm_crtc* crtc; } ;
struct drm_connector {int dummy; } ;
struct drm_atomic_state {int dummy; } ;
struct dc_info_packet {int dummy; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct drm_crtc_state*) ; 
 int PTR_ERR (struct drm_crtc_state*) ; 
 struct drm_crtc_state* drm_atomic_get_crtc_state (struct drm_atomic_state*,struct drm_crtc*) ; 
 struct drm_connector_state* drm_atomic_get_new_connector_state (struct drm_atomic_state*,struct drm_connector*) ; 
 struct drm_connector_state* drm_atomic_get_old_connector_state (struct drm_atomic_state*,struct drm_connector*) ; 
 int fill_hdr_info_packet (struct drm_connector_state*,struct dc_info_packet*) ; 
 scalar_t__ is_hdr_metadata_different (struct drm_connector_state*,struct drm_connector_state*) ; 

__attribute__((used)) static int
amdgpu_dm_connector_atomic_check(struct drm_connector *conn,
				 struct drm_atomic_state *state)
{
	struct drm_connector_state *new_con_state =
		drm_atomic_get_new_connector_state(state, conn);
	struct drm_connector_state *old_con_state =
		drm_atomic_get_old_connector_state(state, conn);
	struct drm_crtc *crtc = new_con_state->crtc;
	struct drm_crtc_state *new_crtc_state;
	int ret;

	if (!crtc)
		return 0;

	if (is_hdr_metadata_different(old_con_state, new_con_state)) {
		struct dc_info_packet hdr_infopacket;

		ret = fill_hdr_info_packet(new_con_state, &hdr_infopacket);
		if (ret)
			return ret;

		new_crtc_state = drm_atomic_get_crtc_state(state, crtc);
		if (IS_ERR(new_crtc_state))
			return PTR_ERR(new_crtc_state);

		/*
		 * DC considers the stream backends changed if the
		 * static metadata changes. Forcing the modeset also
		 * gives a simple way for userspace to switch from
		 * 8bpc to 10bpc when setting the metadata to enter
		 * or exit HDR.
		 *
		 * Changing the static metadata after it's been
		 * set is permissible, however. So only force a
		 * modeset if we're entering or exiting HDR.
		 */
		new_crtc_state->mode_changed =
			!old_con_state->hdr_output_metadata ||
			!new_con_state->hdr_output_metadata;
	}

	return 0;
}