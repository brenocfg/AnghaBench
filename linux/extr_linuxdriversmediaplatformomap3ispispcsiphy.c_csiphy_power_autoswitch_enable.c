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
struct isp_csiphy {int /*<<< orphan*/  cfg_regs; int /*<<< orphan*/  isp; } ;

/* Variables and functions */
 int /*<<< orphan*/  ISPCSI2_PHY_CFG ; 
 int /*<<< orphan*/  ISPCSI2_PHY_CFG_PWR_AUTO ; 
 int /*<<< orphan*/  isp_reg_clr_set (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void csiphy_power_autoswitch_enable(struct isp_csiphy *phy, bool enable)
{
	isp_reg_clr_set(phy->isp, phy->cfg_regs, ISPCSI2_PHY_CFG,
			ISPCSI2_PHY_CFG_PWR_AUTO,
			enable ? ISPCSI2_PHY_CFG_PWR_AUTO : 0);
}