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
struct drm_connector_state {int /*<<< orphan*/  connector; } ;

/* Variables and functions */
 int /*<<< orphan*/  INTEL_OUTPUT_HDMI ; 
 scalar_t__ intel_crtc_has_type (struct intel_crtc_state const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  intel_disable_ddi_dp (struct intel_encoder*,struct intel_crtc_state const*,struct drm_connector_state const*) ; 
 int /*<<< orphan*/  intel_disable_ddi_hdmi (struct intel_encoder*,struct intel_crtc_state const*,struct drm_connector_state const*) ; 
 int /*<<< orphan*/  intel_hdcp_disable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  to_intel_connector (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void intel_disable_ddi(struct intel_encoder *encoder,
			      const struct intel_crtc_state *old_crtc_state,
			      const struct drm_connector_state *old_conn_state)
{
	intel_hdcp_disable(to_intel_connector(old_conn_state->connector));

	if (intel_crtc_has_type(old_crtc_state, INTEL_OUTPUT_HDMI))
		intel_disable_ddi_hdmi(encoder, old_crtc_state, old_conn_state);
	else
		intel_disable_ddi_dp(encoder, old_crtc_state, old_conn_state);
}