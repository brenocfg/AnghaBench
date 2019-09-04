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
typedef  int u32 ;
struct analogix_dp_device {scalar_t__ reg_base; } ;

/* Variables and functions */
 scalar_t__ ANALOGIX_DP_LANE_MAP ; 
 int LANE0_MAP_LOGIC_LANE_0 ; 
 int LANE0_MAP_LOGIC_LANE_3 ; 
 int LANE1_MAP_LOGIC_LANE_1 ; 
 int LANE1_MAP_LOGIC_LANE_2 ; 
 int LANE2_MAP_LOGIC_LANE_1 ; 
 int LANE2_MAP_LOGIC_LANE_2 ; 
 int LANE3_MAP_LOGIC_LANE_0 ; 
 int LANE3_MAP_LOGIC_LANE_3 ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

void analogix_dp_lane_swap(struct analogix_dp_device *dp, bool enable)
{
	u32 reg;

	if (enable)
		reg = LANE3_MAP_LOGIC_LANE_0 | LANE2_MAP_LOGIC_LANE_1 |
		      LANE1_MAP_LOGIC_LANE_2 | LANE0_MAP_LOGIC_LANE_3;
	else
		reg = LANE3_MAP_LOGIC_LANE_3 | LANE2_MAP_LOGIC_LANE_2 |
		      LANE1_MAP_LOGIC_LANE_1 | LANE0_MAP_LOGIC_LANE_0;

	writel(reg, dp->reg_base + ANALOGIX_DP_LANE_MAP);
}