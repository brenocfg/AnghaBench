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
struct intel_dp {int /*<<< orphan*/  aux; } ;
struct intel_crtc_state {int /*<<< orphan*/  fec_enable; } ;

/* Variables and functions */
 int /*<<< orphan*/  DP_FEC_CONFIGURATION ; 
 int /*<<< orphan*/  DP_FEC_READY ; 
 int /*<<< orphan*/  DRM_DEBUG_KMS (char*) ; 
 scalar_t__ drm_dp_dpcd_writeb (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void intel_dp_sink_set_fec_ready(struct intel_dp *intel_dp,
					const struct intel_crtc_state *crtc_state)
{
	if (!crtc_state->fec_enable)
		return;

	if (drm_dp_dpcd_writeb(&intel_dp->aux, DP_FEC_CONFIGURATION, DP_FEC_READY) <= 0)
		DRM_DEBUG_KMS("Failed to set FEC_READY in the sink\n");
}