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
typedef  scalar_t__ uint8_t ;
struct gma_encoder {struct cdv_intel_dp* dev_priv; } ;
struct cdv_intel_dp {int lane_count; scalar_t__* train_set; int /*<<< orphan*/  link_status; } ;

/* Variables and functions */
 scalar_t__ CDV_DP_VOLTAGE_MAX ; 
 scalar_t__ DP_TRAIN_MAX_PRE_EMPHASIS_REACHED ; 
 scalar_t__ DP_TRAIN_MAX_SWING_REACHED ; 
 scalar_t__ DP_TRAIN_PRE_EMPHASIS_MASK ; 
 scalar_t__ cdv_intel_get_adjust_request_pre_emphasis (int /*<<< orphan*/ ,int) ; 
 scalar_t__ cdv_intel_get_adjust_request_voltage (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
cdv_intel_get_adjust_train(struct gma_encoder *encoder)
{
	struct cdv_intel_dp *intel_dp = encoder->dev_priv;
	uint8_t v = 0;
	uint8_t p = 0;
	int lane;

	for (lane = 0; lane < intel_dp->lane_count; lane++) {
		uint8_t this_v = cdv_intel_get_adjust_request_voltage(intel_dp->link_status, lane);
		uint8_t this_p = cdv_intel_get_adjust_request_pre_emphasis(intel_dp->link_status, lane);

		if (this_v > v)
			v = this_v;
		if (this_p > p)
			p = this_p;
	}
	
	if (v >= CDV_DP_VOLTAGE_MAX)
		v = CDV_DP_VOLTAGE_MAX | DP_TRAIN_MAX_SWING_REACHED;

	if (p == DP_TRAIN_PRE_EMPHASIS_MASK)
		p |= DP_TRAIN_MAX_PRE_EMPHASIS_REACHED;
		
	for (lane = 0; lane < 4; lane++)
		intel_dp->train_set[lane] = v | p;
}