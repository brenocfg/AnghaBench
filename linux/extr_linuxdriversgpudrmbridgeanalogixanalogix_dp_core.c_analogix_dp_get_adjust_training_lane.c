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
typedef  scalar_t__ u8 ;
struct TYPE_2__ {int lane_count; scalar_t__* training_lane; } ;
struct analogix_dp_device {TYPE_1__ link_train; } ;

/* Variables and functions */
 scalar_t__ DPCD_PRE_EMPHASIS_SET (scalar_t__) ; 
 scalar_t__ DPCD_VOLTAGE_SWING_SET (scalar_t__) ; 
 scalar_t__ DP_TRAIN_MAX_PRE_EMPHASIS_REACHED ; 
 scalar_t__ DP_TRAIN_MAX_SWING_REACHED ; 
 scalar_t__ PRE_EMPHASIS_LEVEL_3 ; 
 scalar_t__ VOLTAGE_LEVEL_3 ; 
 scalar_t__ analogix_dp_get_adjust_request_pre_emphasis (scalar_t__*,int) ; 
 scalar_t__ analogix_dp_get_adjust_request_voltage (scalar_t__*,int) ; 

__attribute__((used)) static void analogix_dp_get_adjust_training_lane(struct analogix_dp_device *dp,
						 u8 adjust_request[2])
{
	int lane, lane_count;
	u8 voltage_swing, pre_emphasis, training_lane;

	lane_count = dp->link_train.lane_count;
	for (lane = 0; lane < lane_count; lane++) {
		voltage_swing = analogix_dp_get_adjust_request_voltage(
						adjust_request, lane);
		pre_emphasis = analogix_dp_get_adjust_request_pre_emphasis(
						adjust_request, lane);
		training_lane = DPCD_VOLTAGE_SWING_SET(voltage_swing) |
				DPCD_PRE_EMPHASIS_SET(pre_emphasis);

		if (voltage_swing == VOLTAGE_LEVEL_3)
			training_lane |= DP_TRAIN_MAX_SWING_REACHED;
		if (pre_emphasis == PRE_EMPHASIS_LEVEL_3)
			training_lane |= DP_TRAIN_MAX_PRE_EMPHASIS_REACHED;

		dp->link_train.training_lane[lane] = training_lane;
	}
}