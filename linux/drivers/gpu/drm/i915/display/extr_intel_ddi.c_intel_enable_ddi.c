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
typedef  int /*<<< orphan*/  u8 ;
struct intel_encoder {int dummy; } ;
struct intel_crtc_state {int dummy; } ;
struct drm_connector_state {scalar_t__ content_protection; scalar_t__ hdcp_content_type; int /*<<< orphan*/  connector; } ;

/* Variables and functions */
 scalar_t__ DRM_MODE_CONTENT_PROTECTION_DESIRED ; 
 int /*<<< orphan*/  INTEL_OUTPUT_HDMI ; 
 scalar_t__ intel_crtc_has_type (struct intel_crtc_state const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  intel_enable_ddi_dp (struct intel_encoder*,struct intel_crtc_state const*,struct drm_connector_state const*) ; 
 int /*<<< orphan*/  intel_enable_ddi_hdmi (struct intel_encoder*,struct intel_crtc_state const*,struct drm_connector_state const*) ; 
 int /*<<< orphan*/  intel_hdcp_enable (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  to_intel_connector (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void intel_enable_ddi(struct intel_encoder *encoder,
			     const struct intel_crtc_state *crtc_state,
			     const struct drm_connector_state *conn_state)
{
	if (intel_crtc_has_type(crtc_state, INTEL_OUTPUT_HDMI))
		intel_enable_ddi_hdmi(encoder, crtc_state, conn_state);
	else
		intel_enable_ddi_dp(encoder, crtc_state, conn_state);

	/* Enable hdcp if it's desired */
	if (conn_state->content_protection ==
	    DRM_MODE_CONTENT_PROTECTION_DESIRED)
		intel_hdcp_enable(to_intel_connector(conn_state->connector),
				  (u8)conn_state->hdcp_content_type);
}