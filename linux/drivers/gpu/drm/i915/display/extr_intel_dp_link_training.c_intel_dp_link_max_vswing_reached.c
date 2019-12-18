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
struct intel_dp {int lane_count; int* train_set; } ;

/* Variables and functions */
 int DP_TRAIN_MAX_SWING_REACHED ; 

__attribute__((used)) static bool intel_dp_link_max_vswing_reached(struct intel_dp *intel_dp)
{
	int lane;

	for (lane = 0; lane < intel_dp->lane_count; lane++)
		if ((intel_dp->train_set[lane] &
		     DP_TRAIN_MAX_SWING_REACHED) == 0)
			return false;

	return true;
}