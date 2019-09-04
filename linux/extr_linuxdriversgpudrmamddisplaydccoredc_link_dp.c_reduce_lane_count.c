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
typedef  enum dc_lane_count { ____Placeholder_dc_lane_count } dc_lane_count ;

/* Variables and functions */
#define  LANE_COUNT_FOUR 130 
#define  LANE_COUNT_ONE 129 
#define  LANE_COUNT_TWO 128 
 int LANE_COUNT_UNKNOWN ; 

__attribute__((used)) static enum dc_lane_count reduce_lane_count(enum dc_lane_count lane_count)
{
	switch (lane_count) {
	case LANE_COUNT_FOUR:
		return LANE_COUNT_TWO;
	case LANE_COUNT_TWO:
		return LANE_COUNT_ONE;
	case LANE_COUNT_ONE:
		return LANE_COUNT_UNKNOWN;
	default:
		return LANE_COUNT_UNKNOWN;
	}
}