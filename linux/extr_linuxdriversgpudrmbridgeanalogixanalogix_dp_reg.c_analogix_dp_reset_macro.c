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
 scalar_t__ ANALOGIX_DP_PHY_TEST ; 
 int /*<<< orphan*/  MACRO_RST ; 
 int /*<<< orphan*/  readl (scalar_t__) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

void analogix_dp_reset_macro(struct analogix_dp_device *dp)
{
	u32 reg;

	reg = readl(dp->reg_base + ANALOGIX_DP_PHY_TEST);
	reg |= MACRO_RST;
	writel(reg, dp->reg_base + ANALOGIX_DP_PHY_TEST);

	/* 10 us is the minimum reset time. */
	usleep_range(10, 20);

	reg &= ~MACRO_RST;
	writel(reg, dp->reg_base + ANALOGIX_DP_PHY_TEST);
}