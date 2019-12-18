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
struct TYPE_2__ {int /*<<< orphan*/  CR_DONE_0; } ;
union lane_status {TYPE_1__ bits; } ;
typedef  enum link_training_result { ____Placeholder_link_training_result } link_training_result ;
typedef  enum dc_lane_count { ____Placeholder_dc_lane_count } dc_lane_count ;

/* Variables and functions */
 int LANE_COUNT_FOUR ; 
 int LANE_COUNT_ONE ; 
 int LANE_COUNT_TWO ; 
 int LINK_TRAINING_CR_FAIL_LANE0 ; 
 int LINK_TRAINING_CR_FAIL_LANE1 ; 
 int LINK_TRAINING_CR_FAIL_LANE23 ; 
 int LINK_TRAINING_SUCCESS ; 

__attribute__((used)) static enum link_training_result get_cr_failure(enum dc_lane_count ln_count,
					union lane_status *dpcd_lane_status)
{
	enum link_training_result result = LINK_TRAINING_SUCCESS;

	if (ln_count >= LANE_COUNT_ONE && !dpcd_lane_status[0].bits.CR_DONE_0)
		result = LINK_TRAINING_CR_FAIL_LANE0;
	else if (ln_count >= LANE_COUNT_TWO && !dpcd_lane_status[1].bits.CR_DONE_0)
		result = LINK_TRAINING_CR_FAIL_LANE1;
	else if (ln_count >= LANE_COUNT_FOUR && !dpcd_lane_status[2].bits.CR_DONE_0)
		result = LINK_TRAINING_CR_FAIL_LANE23;
	else if (ln_count >= LANE_COUNT_FOUR && !dpcd_lane_status[3].bits.CR_DONE_0)
		result = LINK_TRAINING_CR_FAIL_LANE23;
	return result;
}