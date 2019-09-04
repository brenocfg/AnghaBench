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
typedef  int uint8_t ;
struct intel_dp {int lane_count; int* train_set; int /*<<< orphan*/  dpcd; int /*<<< orphan*/  DP; int /*<<< orphan*/  aux; int /*<<< orphan*/  link_rate; int /*<<< orphan*/  (* prepare_link_retrain ) (struct intel_dp*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  DP_DOWNSPREAD_CTRL ; 
 int DP_LANE_COUNT_ENHANCED_FRAME_EN ; 
 int /*<<< orphan*/  DP_LINK_BW_SET ; 
 int /*<<< orphan*/  DP_LINK_RATE_SET ; 
 int DP_LINK_SCRAMBLING_DISABLE ; 
 int DP_LINK_STATUS_SIZE ; 
 int /*<<< orphan*/  DP_PORT_EN ; 
 int DP_SET_ANSI_8B10B ; 
 int DP_TRAINING_PATTERN_1 ; 
 int DP_TRAIN_VOLTAGE_SWING_MASK ; 
 int /*<<< orphan*/  DRM_DEBUG_KMS (char*,...) ; 
 int /*<<< orphan*/  DRM_ERROR (char*) ; 
 scalar_t__ drm_dp_clock_recovery_ok (int*,int) ; 
 int /*<<< orphan*/  drm_dp_dpcd_write (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int*,int) ; 
 scalar_t__ drm_dp_enhanced_frame_cap (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_dp_link_train_clock_recovery_delay (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  intel_dp_compute_rate (struct intel_dp*,int /*<<< orphan*/ ,int*,int*) ; 
 int /*<<< orphan*/  intel_dp_get_link_status (struct intel_dp*,int*) ; 
 scalar_t__ intel_dp_link_max_vswing_reached (struct intel_dp*) ; 
 int /*<<< orphan*/  intel_dp_reset_link_train (struct intel_dp*,int) ; 
 int /*<<< orphan*/  intel_dp_update_link_train (struct intel_dp*) ; 
 int /*<<< orphan*/  intel_get_adjust_train (struct intel_dp*,int*) ; 
 int /*<<< orphan*/  stub1 (struct intel_dp*) ; 

__attribute__((used)) static bool
intel_dp_link_training_clock_recovery(struct intel_dp *intel_dp)
{
	uint8_t voltage;
	int voltage_tries, max_vswing_tries;
	uint8_t link_config[2];
	uint8_t link_bw, rate_select;

	if (intel_dp->prepare_link_retrain)
		intel_dp->prepare_link_retrain(intel_dp);

	intel_dp_compute_rate(intel_dp, intel_dp->link_rate,
			      &link_bw, &rate_select);

	if (link_bw)
		DRM_DEBUG_KMS("Using LINK_BW_SET value %02x\n", link_bw);
	else
		DRM_DEBUG_KMS("Using LINK_RATE_SET value %02x\n", rate_select);

	/* Write the link configuration data */
	link_config[0] = link_bw;
	link_config[1] = intel_dp->lane_count;
	if (drm_dp_enhanced_frame_cap(intel_dp->dpcd))
		link_config[1] |= DP_LANE_COUNT_ENHANCED_FRAME_EN;
	drm_dp_dpcd_write(&intel_dp->aux, DP_LINK_BW_SET, link_config, 2);

	/* eDP 1.4 rate select method. */
	if (!link_bw)
		drm_dp_dpcd_write(&intel_dp->aux, DP_LINK_RATE_SET,
				  &rate_select, 1);

	link_config[0] = 0;
	link_config[1] = DP_SET_ANSI_8B10B;
	drm_dp_dpcd_write(&intel_dp->aux, DP_DOWNSPREAD_CTRL, link_config, 2);

	intel_dp->DP |= DP_PORT_EN;

	/* clock recovery */
	if (!intel_dp_reset_link_train(intel_dp,
				       DP_TRAINING_PATTERN_1 |
				       DP_LINK_SCRAMBLING_DISABLE)) {
		DRM_ERROR("failed to enable link training\n");
		return false;
	}

	voltage_tries = 1;
	max_vswing_tries = 0;
	for (;;) {
		uint8_t link_status[DP_LINK_STATUS_SIZE];

		drm_dp_link_train_clock_recovery_delay(intel_dp->dpcd);

		if (!intel_dp_get_link_status(intel_dp, link_status)) {
			DRM_ERROR("failed to get link status\n");
			return false;
		}

		if (drm_dp_clock_recovery_ok(link_status, intel_dp->lane_count)) {
			DRM_DEBUG_KMS("clock recovery OK\n");
			return true;
		}

		if (voltage_tries == 5) {
			DRM_DEBUG_KMS("Same voltage tried 5 times\n");
			return false;
		}

		if (max_vswing_tries == 1) {
			DRM_DEBUG_KMS("Max Voltage Swing reached\n");
			return false;
		}

		voltage = intel_dp->train_set[0] & DP_TRAIN_VOLTAGE_SWING_MASK;

		/* Update training set as requested by target */
		intel_get_adjust_train(intel_dp, link_status);
		if (!intel_dp_update_link_train(intel_dp)) {
			DRM_ERROR("failed to update link training\n");
			return false;
		}

		if ((intel_dp->train_set[0] & DP_TRAIN_VOLTAGE_SWING_MASK) ==
		    voltage)
			++voltage_tries;
		else
			voltage_tries = 1;

		if (intel_dp_link_max_vswing_reached(intel_dp))
			++max_vswing_tries;

	}
}