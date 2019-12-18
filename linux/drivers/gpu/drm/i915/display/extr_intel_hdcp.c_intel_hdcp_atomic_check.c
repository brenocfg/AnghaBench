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
typedef  scalar_t__ u64 ;
struct drm_crtc_state {int mode_changed; } ;
struct drm_connector_state {scalar_t__ content_protection; scalar_t__ hdcp_content_type; int /*<<< orphan*/  crtc; int /*<<< orphan*/  state; } ;
struct drm_connector {int dummy; } ;

/* Variables and functions */
 scalar_t__ DRM_MODE_CONTENT_PROTECTION_DESIRED ; 
 scalar_t__ DRM_MODE_CONTENT_PROTECTION_ENABLED ; 
 struct drm_crtc_state* drm_atomic_get_new_crtc_state (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void intel_hdcp_atomic_check(struct drm_connector *connector,
			     struct drm_connector_state *old_state,
			     struct drm_connector_state *new_state)
{
	u64 old_cp = old_state->content_protection;
	u64 new_cp = new_state->content_protection;
	struct drm_crtc_state *crtc_state;

	if (!new_state->crtc) {
		/*
		 * If the connector is being disabled with CP enabled, mark it
		 * desired so it's re-enabled when the connector is brought back
		 */
		if (old_cp == DRM_MODE_CONTENT_PROTECTION_ENABLED)
			new_state->content_protection =
				DRM_MODE_CONTENT_PROTECTION_DESIRED;
		return;
	}

	/*
	 * Nothing to do if the state didn't change, or HDCP was activated since
	 * the last commit. And also no change in hdcp content type.
	 */
	if (old_cp == new_cp ||
	    (old_cp == DRM_MODE_CONTENT_PROTECTION_DESIRED &&
	     new_cp == DRM_MODE_CONTENT_PROTECTION_ENABLED)) {
		if (old_state->hdcp_content_type ==
				new_state->hdcp_content_type)
			return;
	}

	crtc_state = drm_atomic_get_new_crtc_state(new_state->state,
						   new_state->crtc);
	crtc_state->mode_changed = true;
}