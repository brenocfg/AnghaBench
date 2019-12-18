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
 scalar_t__ ANALOGIX_DP_COMMON_INT_MASK_4 ; 
 scalar_t__ ANALOGIX_DP_INT_STA_MASK ; 
 int /*<<< orphan*/  COMMON_INT_MASK_4 ; 
 int /*<<< orphan*/  INT_STA_MASK ; 
 int /*<<< orphan*/  readl (scalar_t__) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

void analogix_dp_mute_hpd_interrupt(struct analogix_dp_device *dp)
{
	u32 reg;

	/* 0: mask, 1: unmask */
	reg = readl(dp->reg_base + ANALOGIX_DP_COMMON_INT_MASK_4);
	reg &= ~COMMON_INT_MASK_4;
	writel(reg, dp->reg_base + ANALOGIX_DP_COMMON_INT_MASK_4);

	reg = readl(dp->reg_base + ANALOGIX_DP_INT_STA_MASK);
	reg &= ~INT_STA_MASK;
	writel(reg, dp->reg_base + ANALOGIX_DP_INT_STA_MASK);
}