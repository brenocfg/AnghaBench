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
typedef  int /*<<< orphan*/  u32 ;
struct intel_dp {int link_rate; int /*<<< orphan*/  dpcd; } ;

/* Variables and functions */
 int /*<<< orphan*/  DP_TRAINING_PATTERN_2 ; 
 int /*<<< orphan*/  DP_TRAINING_PATTERN_3 ; 
 int /*<<< orphan*/  DP_TRAINING_PATTERN_4 ; 
 int /*<<< orphan*/  DRM_DEBUG_KMS (char*) ; 
 int drm_dp_tps3_supported (int /*<<< orphan*/ ) ; 
 int drm_dp_tps4_supported (int /*<<< orphan*/ ) ; 
 int intel_dp_source_supports_hbr2 (struct intel_dp*) ; 
 int intel_dp_source_supports_hbr3 (struct intel_dp*) ; 

__attribute__((used)) static u32 intel_dp_training_pattern(struct intel_dp *intel_dp)
{
	bool source_tps3, sink_tps3, source_tps4, sink_tps4;

	/*
	 * Intel platforms that support HBR3 also support TPS4. It is mandatory
	 * for all downstream devices that support HBR3. There are no known eDP
	 * panels that support TPS4 as of Feb 2018 as per VESA eDP_v1.4b_E1
	 * specification.
	 */
	source_tps4 = intel_dp_source_supports_hbr3(intel_dp);
	sink_tps4 = drm_dp_tps4_supported(intel_dp->dpcd);
	if (source_tps4 && sink_tps4) {
		return DP_TRAINING_PATTERN_4;
	} else if (intel_dp->link_rate == 810000) {
		if (!source_tps4)
			DRM_DEBUG_KMS("8.1 Gbps link rate without source HBR3/TPS4 support\n");
		if (!sink_tps4)
			DRM_DEBUG_KMS("8.1 Gbps link rate without sink TPS4 support\n");
	}
	/*
	 * Intel platforms that support HBR2 also support TPS3. TPS3 support is
	 * also mandatory for downstream devices that support HBR2. However, not
	 * all sinks follow the spec.
	 */
	source_tps3 = intel_dp_source_supports_hbr2(intel_dp);
	sink_tps3 = drm_dp_tps3_supported(intel_dp->dpcd);
	if (source_tps3 && sink_tps3) {
		return  DP_TRAINING_PATTERN_3;
	} else if (intel_dp->link_rate >= 540000) {
		if (!source_tps3)
			DRM_DEBUG_KMS(">=5.4/6.48 Gbps link rate without source HBR2/TPS3 support\n");
		if (!sink_tps3)
			DRM_DEBUG_KMS(">=5.4/6.48 Gbps link rate without sink TPS3 support\n");
	}

	return DP_TRAINING_PATTERN_2;
}