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
struct gma_encoder {struct cdv_intel_dp* dev_priv; } ;
struct cdv_intel_dp {int* dpcd; } ;

/* Variables and functions */
 size_t DP_DPCD_REV ; 
 int /*<<< orphan*/  DP_SET_POWER ; 
 int /*<<< orphan*/  DP_SET_POWER_D0 ; 
 int /*<<< orphan*/  DP_SET_POWER_D3 ; 
 int /*<<< orphan*/  DRM_DEBUG_DRIVER (char*) ; 
 int DRM_MODE_DPMS_ON ; 
 int cdv_intel_dp_aux_native_write_1 (struct gma_encoder*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static void cdv_intel_dp_sink_dpms(struct gma_encoder *encoder, int mode)
{
	struct cdv_intel_dp *intel_dp = encoder->dev_priv;
	int ret, i;

	/* Should have a valid DPCD by this point */
	if (intel_dp->dpcd[DP_DPCD_REV] < 0x11)
		return;

	if (mode != DRM_MODE_DPMS_ON) {
		ret = cdv_intel_dp_aux_native_write_1(encoder, DP_SET_POWER,
						  DP_SET_POWER_D3);
		if (ret != 1)
			DRM_DEBUG_DRIVER("failed to write sink power state\n");
	} else {
		/*
		 * When turning on, we need to retry for 1ms to give the sink
		 * time to wake up.
		 */
		for (i = 0; i < 3; i++) {
			ret = cdv_intel_dp_aux_native_write_1(encoder,
							  DP_SET_POWER,
							  DP_SET_POWER_D0);
			if (ret == 1)
				break;
			udelay(1000);
		}
	}
}