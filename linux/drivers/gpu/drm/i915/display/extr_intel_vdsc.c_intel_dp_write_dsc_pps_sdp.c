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
struct intel_encoder {int /*<<< orphan*/  base; } ;
struct intel_dp {int dummy; } ;
struct intel_digital_port {int /*<<< orphan*/  (* write_infoframe ) (struct intel_encoder*,struct intel_crtc_state const*,int /*<<< orphan*/ ,struct drm_dsc_pps_infoframe*,int) ;} ;
struct drm_dsc_config {int dummy; } ;
struct intel_crtc_state {struct drm_dsc_config dp_dsc_cfg; } ;
struct drm_dsc_pps_infoframe {int /*<<< orphan*/  pps_payload; int /*<<< orphan*/  pps_header; } ;
typedef  int /*<<< orphan*/  dp_dsc_pps_sdp ;

/* Variables and functions */
 int /*<<< orphan*/  DP_SDP_PPS ; 
 struct intel_digital_port* dp_to_dig_port (struct intel_dp*) ; 
 int /*<<< orphan*/  drm_dsc_dp_pps_header_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  drm_dsc_pps_payload_pack (int /*<<< orphan*/ *,struct drm_dsc_config const*) ; 
 struct intel_dp* enc_to_intel_dp (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct intel_encoder*,struct intel_crtc_state const*,int /*<<< orphan*/ ,struct drm_dsc_pps_infoframe*,int) ; 

__attribute__((used)) static void intel_dp_write_dsc_pps_sdp(struct intel_encoder *encoder,
				       const struct intel_crtc_state *crtc_state)
{
	struct intel_dp *intel_dp = enc_to_intel_dp(&encoder->base);
	struct intel_digital_port *intel_dig_port = dp_to_dig_port(intel_dp);
	const struct drm_dsc_config *vdsc_cfg = &crtc_state->dp_dsc_cfg;
	struct drm_dsc_pps_infoframe dp_dsc_pps_sdp;

	/* Prepare DP SDP PPS header as per DP 1.4 spec, Table 2-123 */
	drm_dsc_dp_pps_header_init(&dp_dsc_pps_sdp.pps_header);

	/* Fill the PPS payload bytes as per DSC spec 1.2 Table 4-1 */
	drm_dsc_pps_payload_pack(&dp_dsc_pps_sdp.pps_payload, vdsc_cfg);

	intel_dig_port->write_infoframe(encoder, crtc_state,
					DP_SDP_PPS, &dp_dsc_pps_sdp,
					sizeof(dp_dsc_pps_sdp));
}