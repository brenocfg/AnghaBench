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
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_2__ {int lane_count; int /*<<< orphan*/ * training_lane; int /*<<< orphan*/  link_rate; } ;
struct analogix_dp_device {int /*<<< orphan*/  dev; TYPE_1__ link_train; int /*<<< orphan*/  aux; } ;
typedef  enum pll_status { ____Placeholder_pll_status } pll_status ;

/* Variables and functions */
 int /*<<< orphan*/  DP_LANE0_1_STATUS ; 
 int /*<<< orphan*/  DP_LANE_ALIGN_STATUS_UPDATED ; 
 int /*<<< orphan*/  DP_NONE ; 
 int DP_TIMEOUT_LOOP_COUNT ; 
 int /*<<< orphan*/  DRM_DEV_ERROR (int /*<<< orphan*/ ,char*,...) ; 
 int EIO ; 
 int PLL_UNLOCKED ; 
 int /*<<< orphan*/  TRAINING_PTN1 ; 
 int /*<<< orphan*/  TRAINING_PTN2 ; 
 scalar_t__ analogix_dp_channel_eq_ok (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 scalar_t__ analogix_dp_clock_recovery_ok (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  analogix_dp_get_pll_lock_status ; 
 int /*<<< orphan*/  analogix_dp_reduce_link_rate (struct analogix_dp_device*) ; 
 int /*<<< orphan*/  analogix_dp_reset_macro (struct analogix_dp_device*) ; 
 int /*<<< orphan*/  analogix_dp_set_lane_count (struct analogix_dp_device*,int) ; 
 int /*<<< orphan*/  analogix_dp_set_lane_link_training (struct analogix_dp_device*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  analogix_dp_set_link_bandwidth (struct analogix_dp_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  analogix_dp_set_training_pattern (struct analogix_dp_device*,int /*<<< orphan*/ ) ; 
 int drm_dp_dpcd_read (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int drm_dp_dpcd_readb (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int readx_poll_timeout (int /*<<< orphan*/ ,struct analogix_dp_device*,int,int,int,int) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 
 scalar_t__ verify_fast_training ; 

__attribute__((used)) static int analogix_dp_fast_link_train(struct analogix_dp_device *dp)
{
	int i, ret;
	u8 link_align, link_status[2];
	enum pll_status status;

	analogix_dp_reset_macro(dp);

	analogix_dp_set_link_bandwidth(dp, dp->link_train.link_rate);
	analogix_dp_set_lane_count(dp, dp->link_train.lane_count);

	for (i = 0; i < dp->link_train.lane_count; i++) {
		analogix_dp_set_lane_link_training(dp,
			dp->link_train.training_lane[i], i);
	}

	ret = readx_poll_timeout(analogix_dp_get_pll_lock_status, dp, status,
				 status != PLL_UNLOCKED, 120,
				 120 * DP_TIMEOUT_LOOP_COUNT);
	if (ret) {
		DRM_DEV_ERROR(dp->dev, "Wait for pll lock failed %d\n", ret);
		return ret;
	}

	/* source Set training pattern 1 */
	analogix_dp_set_training_pattern(dp, TRAINING_PTN1);
	/* From DP spec, pattern must be on-screen for a minimum 500us */
	usleep_range(500, 600);

	analogix_dp_set_training_pattern(dp, TRAINING_PTN2);
	/* From DP spec, pattern must be on-screen for a minimum 500us */
	usleep_range(500, 600);

	/* TODO: enhanced_mode?*/
	analogix_dp_set_training_pattern(dp, DP_NONE);

	/*
	 * Useful for debugging issues with fast link training, disable for more
	 * speed
	 */
	if (verify_fast_training) {
		ret = drm_dp_dpcd_readb(&dp->aux, DP_LANE_ALIGN_STATUS_UPDATED,
					&link_align);
		if (ret < 0) {
			DRM_DEV_ERROR(dp->dev, "Read align status failed %d\n",
				      ret);
			return ret;
		}

		ret = drm_dp_dpcd_read(&dp->aux, DP_LANE0_1_STATUS, link_status,
				       2);
		if (ret < 0) {
			DRM_DEV_ERROR(dp->dev, "Read link status failed %d\n",
				      ret);
			return ret;
		}

		if (analogix_dp_clock_recovery_ok(link_status,
						  dp->link_train.lane_count)) {
			DRM_DEV_ERROR(dp->dev, "Clock recovery failed\n");
			analogix_dp_reduce_link_rate(dp);
			return -EIO;
		}

		if (analogix_dp_channel_eq_ok(link_status, link_align,
					      dp->link_train.lane_count)) {
			DRM_DEV_ERROR(dp->dev, "Channel EQ failed\n");
			analogix_dp_reduce_link_rate(dp);
			return -EIO;
		}
	}

	return 0;
}