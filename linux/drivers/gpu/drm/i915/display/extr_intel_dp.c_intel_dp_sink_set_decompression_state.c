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
struct intel_dp {int /*<<< orphan*/  aux; } ;
struct TYPE_2__ {int /*<<< orphan*/  compression_enable; } ;
struct intel_crtc_state {TYPE_1__ dsc_params; } ;

/* Variables and functions */
 int /*<<< orphan*/  DP_DECOMPRESSION_EN ; 
 int /*<<< orphan*/  DP_DSC_ENABLE ; 
 int /*<<< orphan*/  DRM_DEBUG_KMS (char*,char*) ; 
 int drm_dp_dpcd_writeb (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void intel_dp_sink_set_decompression_state(struct intel_dp *intel_dp,
					   const struct intel_crtc_state *crtc_state,
					   bool enable)
{
	int ret;

	if (!crtc_state->dsc_params.compression_enable)
		return;

	ret = drm_dp_dpcd_writeb(&intel_dp->aux, DP_DSC_ENABLE,
				 enable ? DP_DECOMPRESSION_EN : 0);
	if (ret < 0)
		DRM_DEBUG_KMS("Failed to %s sink decompression state\n",
			      enable ? "enable" : "disable");
}