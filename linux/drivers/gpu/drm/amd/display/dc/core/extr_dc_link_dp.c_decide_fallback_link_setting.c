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
struct dc_link_settings {void* link_rate; void* lane_count; } ;
typedef  enum link_training_result { ____Placeholder_link_training_result } link_training_result ;

/* Variables and functions */
 void* LANE_COUNT_ONE ; 
 void* LANE_COUNT_TWO ; 
#define  LINK_TRAINING_CR_FAIL_LANE0 133 
#define  LINK_TRAINING_CR_FAIL_LANE1 132 
#define  LINK_TRAINING_CR_FAIL_LANE23 131 
#define  LINK_TRAINING_EQ_FAIL_CR 130 
#define  LINK_TRAINING_EQ_FAIL_EQ 129 
#define  LINK_TRAINING_LQA_FAIL 128 
 int /*<<< orphan*/  reached_minimum_lane_count (void*) ; 
 int /*<<< orphan*/  reached_minimum_link_rate (void*) ; 
 void* reduce_lane_count (void*) ; 
 void* reduce_link_rate (void*) ; 

__attribute__((used)) static bool decide_fallback_link_setting(
		struct dc_link_settings initial_link_settings,
		struct dc_link_settings *current_link_setting,
		enum link_training_result training_result)
{
	if (!current_link_setting)
		return false;

	switch (training_result) {
	case LINK_TRAINING_CR_FAIL_LANE0:
	case LINK_TRAINING_CR_FAIL_LANE1:
	case LINK_TRAINING_CR_FAIL_LANE23:
	case LINK_TRAINING_LQA_FAIL:
	{
		if (!reached_minimum_link_rate
				(current_link_setting->link_rate)) {
			current_link_setting->link_rate =
				reduce_link_rate(
					current_link_setting->link_rate);
		} else if (!reached_minimum_lane_count
				(current_link_setting->lane_count)) {
			current_link_setting->link_rate =
				initial_link_settings.link_rate;
			if (training_result == LINK_TRAINING_CR_FAIL_LANE0)
				return false;
			else if (training_result == LINK_TRAINING_CR_FAIL_LANE1)
				current_link_setting->lane_count =
						LANE_COUNT_ONE;
			else if (training_result ==
					LINK_TRAINING_CR_FAIL_LANE23)
				current_link_setting->lane_count =
						LANE_COUNT_TWO;
			else
				current_link_setting->lane_count =
					reduce_lane_count(
					current_link_setting->lane_count);
		} else {
			return false;
		}
		break;
	}
	case LINK_TRAINING_EQ_FAIL_EQ:
	{
		if (!reached_minimum_lane_count
				(current_link_setting->lane_count)) {
			current_link_setting->lane_count =
				reduce_lane_count(
					current_link_setting->lane_count);
		} else if (!reached_minimum_link_rate
				(current_link_setting->link_rate)) {
			current_link_setting->link_rate =
				reduce_link_rate(
					current_link_setting->link_rate);
		} else {
			return false;
		}
		break;
	}
	case LINK_TRAINING_EQ_FAIL_CR:
	{
		if (!reached_minimum_link_rate
				(current_link_setting->link_rate)) {
			current_link_setting->link_rate =
				reduce_link_rate(
					current_link_setting->link_rate);
		} else {
			return false;
		}
		break;
	}
	default:
		return false;
	}
	return true;
}