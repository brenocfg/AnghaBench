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
typedef  int u8 ;
struct intel_dp {int max_link_lane_count; int /*<<< orphan*/  max_link_rate; int /*<<< orphan*/ * common_rates; int /*<<< orphan*/  num_common_rates; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG_KMS (char*) ; 
 int /*<<< orphan*/  DRM_ERROR (char*) ; 
 int /*<<< orphan*/  intel_dp_can_link_train_fallback_for_edp (struct intel_dp*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ intel_dp_is_edp (struct intel_dp*) ; 
 int /*<<< orphan*/  intel_dp_max_common_rate (struct intel_dp*) ; 
 int intel_dp_rate_index (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

int intel_dp_get_link_train_fallback_values(struct intel_dp *intel_dp,
					    int link_rate, u8 lane_count)
{
	int index;

	index = intel_dp_rate_index(intel_dp->common_rates,
				    intel_dp->num_common_rates,
				    link_rate);
	if (index > 0) {
		if (intel_dp_is_edp(intel_dp) &&
		    !intel_dp_can_link_train_fallback_for_edp(intel_dp,
							      intel_dp->common_rates[index - 1],
							      lane_count)) {
			DRM_DEBUG_KMS("Retrying Link training for eDP with same parameters\n");
			return 0;
		}
		intel_dp->max_link_rate = intel_dp->common_rates[index - 1];
		intel_dp->max_link_lane_count = lane_count;
	} else if (lane_count > 1) {
		if (intel_dp_is_edp(intel_dp) &&
		    !intel_dp_can_link_train_fallback_for_edp(intel_dp,
							      intel_dp_max_common_rate(intel_dp),
							      lane_count >> 1)) {
			DRM_DEBUG_KMS("Retrying Link training for eDP with same parameters\n");
			return 0;
		}
		intel_dp->max_link_rate = intel_dp_max_common_rate(intel_dp);
		intel_dp->max_link_lane_count = lane_count >> 1;
	} else {
		DRM_ERROR("Link Training Unsuccessful\n");
		return -1;
	}

	return 0;
}