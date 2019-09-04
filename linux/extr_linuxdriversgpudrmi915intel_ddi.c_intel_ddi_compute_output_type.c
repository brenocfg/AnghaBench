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
struct intel_encoder {int dummy; } ;
struct intel_crtc_state {int dummy; } ;
struct drm_connector_state {TYPE_1__* connector; } ;
typedef  enum intel_output_type { ____Placeholder_intel_output_type } intel_output_type ;
struct TYPE_2__ {int connector_type; } ;

/* Variables and functions */
#define  DRM_MODE_CONNECTOR_DisplayPort 130 
#define  DRM_MODE_CONNECTOR_HDMIA 129 
#define  DRM_MODE_CONNECTOR_eDP 128 
 int INTEL_OUTPUT_DP ; 
 int INTEL_OUTPUT_EDP ; 
 int INTEL_OUTPUT_HDMI ; 
 int INTEL_OUTPUT_UNUSED ; 
 int /*<<< orphan*/  MISSING_CASE (int) ; 

__attribute__((used)) static enum intel_output_type
intel_ddi_compute_output_type(struct intel_encoder *encoder,
			      struct intel_crtc_state *crtc_state,
			      struct drm_connector_state *conn_state)
{
	switch (conn_state->connector->connector_type) {
	case DRM_MODE_CONNECTOR_HDMIA:
		return INTEL_OUTPUT_HDMI;
	case DRM_MODE_CONNECTOR_eDP:
		return INTEL_OUTPUT_EDP;
	case DRM_MODE_CONNECTOR_DisplayPort:
		return INTEL_OUTPUT_DP;
	default:
		MISSING_CASE(conn_state->connector->connector_type);
		return INTEL_OUTPUT_UNUSED;
	}
}