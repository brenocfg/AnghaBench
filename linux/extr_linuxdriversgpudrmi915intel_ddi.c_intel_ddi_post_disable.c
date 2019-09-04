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
struct intel_encoder {int dummy; } ;
struct intel_crtc_state {int dummy; } ;
struct drm_connector_state {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  INTEL_OUTPUT_HDMI ; 
 scalar_t__ intel_crtc_has_type (struct intel_crtc_state const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  intel_ddi_post_disable_dp (struct intel_encoder*,struct intel_crtc_state const*,struct drm_connector_state const*) ; 
 int /*<<< orphan*/  intel_ddi_post_disable_hdmi (struct intel_encoder*,struct intel_crtc_state const*,struct drm_connector_state const*) ; 

__attribute__((used)) static void intel_ddi_post_disable(struct intel_encoder *encoder,
				   const struct intel_crtc_state *old_crtc_state,
				   const struct drm_connector_state *old_conn_state)
{
	/*
	 * When called from DP MST code:
	 * - old_conn_state will be NULL
	 * - encoder will be the main encoder (ie. mst->primary)
	 * - the main connector associated with this port
	 *   won't be active or linked to a crtc
	 * - old_crtc_state will be the state of the last stream to
	 *   be deactivated on this port, and it may not be the same
	 *   stream that was activated last, but each stream
	 *   should have a state that is identical when it comes to
	 *   the DP link parameteres
	 */

	if (intel_crtc_has_type(old_crtc_state, INTEL_OUTPUT_HDMI))
		intel_ddi_post_disable_hdmi(encoder,
					    old_crtc_state, old_conn_state);
	else
		intel_ddi_post_disable_dp(encoder,
					  old_crtc_state, old_conn_state);
}