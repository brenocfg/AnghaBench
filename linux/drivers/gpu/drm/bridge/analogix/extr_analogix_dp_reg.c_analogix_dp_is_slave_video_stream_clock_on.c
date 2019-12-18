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
struct analogix_dp_device {int /*<<< orphan*/  dev; scalar_t__ reg_base; } ;

/* Variables and functions */
 scalar_t__ ANALOGIX_DP_SYS_CTL_1 ; 
 scalar_t__ ANALOGIX_DP_SYS_CTL_2 ; 
 int CHA_STA ; 
 int DET_STA ; 
 int EINVAL ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*) ; 
 int readl (scalar_t__) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

int analogix_dp_is_slave_video_stream_clock_on(struct analogix_dp_device *dp)
{
	u32 reg;

	reg = readl(dp->reg_base + ANALOGIX_DP_SYS_CTL_1);
	writel(reg, dp->reg_base + ANALOGIX_DP_SYS_CTL_1);

	reg = readl(dp->reg_base + ANALOGIX_DP_SYS_CTL_1);

	if (!(reg & DET_STA)) {
		dev_dbg(dp->dev, "Input stream clock not detected.\n");
		return -EINVAL;
	}

	reg = readl(dp->reg_base + ANALOGIX_DP_SYS_CTL_2);
	writel(reg, dp->reg_base + ANALOGIX_DP_SYS_CTL_2);

	reg = readl(dp->reg_base + ANALOGIX_DP_SYS_CTL_2);
	dev_dbg(dp->dev, "wait SYS_CTL_2.\n");

	if (reg & CHA_STA) {
		dev_dbg(dp->dev, "Input stream clk is changing\n");
		return -EINVAL;
	}

	return 0;
}