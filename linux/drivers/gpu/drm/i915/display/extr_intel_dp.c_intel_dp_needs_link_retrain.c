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
struct intel_dp {int /*<<< orphan*/  lane_count; int /*<<< orphan*/  link_rate; int /*<<< orphan*/  link_trained; } ;

/* Variables and functions */
 int DP_LINK_STATUS_SIZE ; 
 int /*<<< orphan*/  drm_dp_channel_eq_ok (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  intel_dp_get_link_status (struct intel_dp*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  intel_dp_link_params_valid (struct intel_dp*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ intel_psr_enabled (struct intel_dp*) ; 

__attribute__((used)) static bool
intel_dp_needs_link_retrain(struct intel_dp *intel_dp)
{
	u8 link_status[DP_LINK_STATUS_SIZE];

	if (!intel_dp->link_trained)
		return false;

	/*
	 * While PSR source HW is enabled, it will control main-link sending
	 * frames, enabling and disabling it so trying to do a retrain will fail
	 * as the link would or not be on or it could mix training patterns
	 * and frame data at the same time causing retrain to fail.
	 * Also when exiting PSR, HW will retrain the link anyways fixing
	 * any link status error.
	 */
	if (intel_psr_enabled(intel_dp))
		return false;

	if (!intel_dp_get_link_status(intel_dp, link_status))
		return false;

	/*
	 * Validate the cached values of intel_dp->link_rate and
	 * intel_dp->lane_count before attempting to retrain.
	 */
	if (!intel_dp_link_params_valid(intel_dp, intel_dp->link_rate,
					intel_dp->lane_count))
		return false;

	/* Retrain if Channel EQ or CR not ok */
	return !drm_dp_channel_eq_ok(link_status, intel_dp->lane_count);
}