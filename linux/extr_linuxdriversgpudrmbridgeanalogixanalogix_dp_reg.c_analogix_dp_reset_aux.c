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
 scalar_t__ ANALOGIX_DP_FUNC_EN_2 ; 
 int /*<<< orphan*/  AUX_FUNC_EN_N ; 
 int /*<<< orphan*/  readl (scalar_t__) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

void analogix_dp_reset_aux(struct analogix_dp_device *dp)
{
	u32 reg;

	/* Disable AUX channel module */
	reg = readl(dp->reg_base + ANALOGIX_DP_FUNC_EN_2);
	reg |= AUX_FUNC_EN_N;
	writel(reg, dp->reg_base + ANALOGIX_DP_FUNC_EN_2);
}