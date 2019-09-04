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
typedef  int u32 ;
struct analogix_dp_device {int reg_base; TYPE_1__* plat_data; } ;
typedef  enum analog_power_block { ____Placeholder_analog_power_block } analog_power_block ;
struct TYPE_2__ {int /*<<< orphan*/  dev_type; } ;

/* Variables and functions */
 int ANALOGIX_DP_PD ; 
 int ANALOGIX_DP_PHY_PD ; 
#define  ANALOG_TOTAL 134 
#define  AUX_BLOCK 133 
 int AUX_PD ; 
#define  CH0_BLOCK 132 
 int CH0_PD ; 
#define  CH1_BLOCK 131 
 int CH1_PD ; 
#define  CH2_BLOCK 130 
 int CH2_PD ; 
#define  CH3_BLOCK 129 
 int CH3_PD ; 
 int DP_ALL_PD ; 
 int DP_INC_BG ; 
 int DP_PHY_PD ; 
#define  POWER_ALL 128 
 int RK_AUX_PD ; 
 scalar_t__ is_rockchip (int /*<<< orphan*/ ) ; 
 int readl (int) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 
 int /*<<< orphan*/  writel (int,int) ; 

void analogix_dp_set_analog_power_down(struct analogix_dp_device *dp,
				       enum analog_power_block block,
				       bool enable)
{
	u32 reg;
	u32 phy_pd_addr = ANALOGIX_DP_PHY_PD;
	u32 mask;

	if (dp->plat_data && is_rockchip(dp->plat_data->dev_type))
		phy_pd_addr = ANALOGIX_DP_PD;

	switch (block) {
	case AUX_BLOCK:
		if (dp->plat_data && is_rockchip(dp->plat_data->dev_type))
			mask = RK_AUX_PD;
		else
			mask = AUX_PD;

		reg = readl(dp->reg_base + phy_pd_addr);
		if (enable)
			reg |= mask;
		else
			reg &= ~mask;
		writel(reg, dp->reg_base + phy_pd_addr);
		break;
	case CH0_BLOCK:
		mask = CH0_PD;
		reg = readl(dp->reg_base + phy_pd_addr);

		if (enable)
			reg |= mask;
		else
			reg &= ~mask;
		writel(reg, dp->reg_base + phy_pd_addr);
		break;
	case CH1_BLOCK:
		mask = CH1_PD;
		reg = readl(dp->reg_base + phy_pd_addr);

		if (enable)
			reg |= mask;
		else
			reg &= ~mask;
		writel(reg, dp->reg_base + phy_pd_addr);
		break;
	case CH2_BLOCK:
		mask = CH2_PD;
		reg = readl(dp->reg_base + phy_pd_addr);

		if (enable)
			reg |= mask;
		else
			reg &= ~mask;
		writel(reg, dp->reg_base + phy_pd_addr);
		break;
	case CH3_BLOCK:
		mask = CH3_PD;
		reg = readl(dp->reg_base + phy_pd_addr);

		if (enable)
			reg |= mask;
		else
			reg &= ~mask;
		writel(reg, dp->reg_base + phy_pd_addr);
		break;
	case ANALOG_TOTAL:
		/*
		 * There is no bit named DP_PHY_PD, so We used DP_INC_BG
		 * to power off everything instead of DP_PHY_PD in
		 * Rockchip
		 */
		if (dp->plat_data && is_rockchip(dp->plat_data->dev_type))
			mask = DP_INC_BG;
		else
			mask = DP_PHY_PD;

		reg = readl(dp->reg_base + phy_pd_addr);
		if (enable)
			reg |= mask;
		else
			reg &= ~mask;

		writel(reg, dp->reg_base + phy_pd_addr);
		if (dp->plat_data && is_rockchip(dp->plat_data->dev_type))
			usleep_range(10, 15);
		break;
	case POWER_ALL:
		if (enable) {
			reg = DP_ALL_PD;
			writel(reg, dp->reg_base + phy_pd_addr);
		} else {
			reg = DP_ALL_PD;
			writel(reg, dp->reg_base + phy_pd_addr);
			usleep_range(10, 15);
			reg &= ~DP_INC_BG;
			writel(reg, dp->reg_base + phy_pd_addr);
			usleep_range(10, 15);

			writel(0x00, dp->reg_base + phy_pd_addr);
		}
		break;
	default:
		break;
	}
}