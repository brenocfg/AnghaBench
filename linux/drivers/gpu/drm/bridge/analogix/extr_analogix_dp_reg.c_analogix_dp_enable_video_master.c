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
 scalar_t__ ANALOGIX_DP_SOC_GENERAL_CTL ; 
 int VIDEO_MASTER_MODE_EN ; 
 int VIDEO_MODE_MASK ; 
 int VIDEO_MODE_MASTER_MODE ; 
 int VIDEO_MODE_SLAVE_MODE ; 
 int readl (scalar_t__) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

void analogix_dp_enable_video_master(struct analogix_dp_device *dp, bool enable)
{
	u32 reg;

	if (enable) {
		reg = readl(dp->reg_base + ANALOGIX_DP_SOC_GENERAL_CTL);
		reg &= ~VIDEO_MODE_MASK;
		reg |= VIDEO_MASTER_MODE_EN | VIDEO_MODE_MASTER_MODE;
		writel(reg, dp->reg_base + ANALOGIX_DP_SOC_GENERAL_CTL);
	} else {
		reg = readl(dp->reg_base + ANALOGIX_DP_SOC_GENERAL_CTL);
		reg &= ~VIDEO_MODE_MASK;
		reg |= VIDEO_MODE_SLAVE_MODE;
		writel(reg, dp->reg_base + ANALOGIX_DP_SOC_GENERAL_CTL);
	}
}