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
typedef  scalar_t__ u32 ;
struct edp_phy {scalar_t__ base; } ;

/* Variables and functions */
 scalar_t__ EDP_MAX_LANE ; 
 scalar_t__ REG_EDP_PHY_LN_PD_CTL (scalar_t__) ; 
 int /*<<< orphan*/  edp_write (scalar_t__,scalar_t__) ; 

void msm_edp_phy_lane_power_ctrl(struct edp_phy *phy, bool up, u32 max_lane)
{
	u32 i;
	u32 data;

	if (up)
		data = 0;	/* power up */
	else
		data = 0x7;	/* power down */

	for (i = 0; i < max_lane; i++)
		edp_write(phy->base + REG_EDP_PHY_LN_PD_CTL(i) , data);

	/* power down unused lane */
	data = 0x7;	/* power down */
	for (i = max_lane; i < EDP_MAX_LANE; i++)
		edp_write(phy->base + REG_EDP_PHY_LN_PD_CTL(i) , data);
}