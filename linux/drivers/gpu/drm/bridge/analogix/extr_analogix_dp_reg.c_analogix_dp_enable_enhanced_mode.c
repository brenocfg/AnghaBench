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
typedef  int /*<<< orphan*/  u32 ;
struct analogix_dp_device {scalar_t__ reg_base; } ;

/* Variables and functions */
 scalar_t__ ANALOGIX_DP_SYS_CTL_4 ; 
 int /*<<< orphan*/  ENHANCED ; 
 int /*<<< orphan*/  readl (scalar_t__) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

void analogix_dp_enable_enhanced_mode(struct analogix_dp_device *dp,
				      bool enable)
{
	u32 reg;

	if (enable) {
		reg = readl(dp->reg_base + ANALOGIX_DP_SYS_CTL_4);
		reg |= ENHANCED;
		writel(reg, dp->reg_base + ANALOGIX_DP_SYS_CTL_4);
	} else {
		reg = readl(dp->reg_base + ANALOGIX_DP_SYS_CTL_4);
		reg &= ~ENHANCED;
		writel(reg, dp->reg_base + ANALOGIX_DP_SYS_CTL_4);
	}
}