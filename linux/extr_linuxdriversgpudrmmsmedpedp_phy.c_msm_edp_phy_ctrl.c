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
struct edp_phy {scalar_t__ base; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG (char*,int) ; 
 int EDP_PHY_CTRL_SW_RESET ; 
 int EDP_PHY_CTRL_SW_RESET_PLL ; 
 scalar_t__ REG_EDP_PHY_CTRL ; 
 scalar_t__ REG_EDP_PHY_GLB_CFG ; 
 scalar_t__ REG_EDP_PHY_GLB_PD_CTL ; 
 int /*<<< orphan*/  edp_write (scalar_t__,int) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 
 int /*<<< orphan*/  wmb () ; 

void msm_edp_phy_ctrl(struct edp_phy *phy, int enable)
{
	DBG("enable=%d", enable);
	if (enable) {
		/* Reset */
		edp_write(phy->base + REG_EDP_PHY_CTRL,
			EDP_PHY_CTRL_SW_RESET | EDP_PHY_CTRL_SW_RESET_PLL);
		/* Make sure fully reset */
		wmb();
		usleep_range(500, 1000);
		edp_write(phy->base + REG_EDP_PHY_CTRL, 0x000);
		edp_write(phy->base + REG_EDP_PHY_GLB_PD_CTL, 0x3f);
		edp_write(phy->base + REG_EDP_PHY_GLB_CFG, 0x1);
	} else {
		edp_write(phy->base + REG_EDP_PHY_GLB_PD_CTL, 0xc0);
	}
}