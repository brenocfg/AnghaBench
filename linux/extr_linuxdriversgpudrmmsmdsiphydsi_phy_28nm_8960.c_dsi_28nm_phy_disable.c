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
struct msm_dsi_phy {scalar_t__ base; } ;

/* Variables and functions */
 scalar_t__ REG_DSI_28nm_8960_PHY_CTRL_0 ; 
 int /*<<< orphan*/  dsi_phy_write (scalar_t__,int) ; 
 int /*<<< orphan*/  wmb () ; 

__attribute__((used)) static void dsi_28nm_phy_disable(struct msm_dsi_phy *phy)
{
	dsi_phy_write(phy->base + REG_DSI_28nm_8960_PHY_CTRL_0, 0x0);

	/*
	 * Wait for the registers writes to complete in order to
	 * ensure that the phy is completely disabled
	 */
	wmb();
}