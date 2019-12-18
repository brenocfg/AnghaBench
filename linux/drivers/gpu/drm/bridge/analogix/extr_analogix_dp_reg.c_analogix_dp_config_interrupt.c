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
 scalar_t__ ANALOGIX_DP_COMMON_INT_MASK_1 ; 
 scalar_t__ ANALOGIX_DP_COMMON_INT_MASK_2 ; 
 scalar_t__ ANALOGIX_DP_COMMON_INT_MASK_3 ; 
 scalar_t__ ANALOGIX_DP_COMMON_INT_MASK_4 ; 
 scalar_t__ ANALOGIX_DP_INT_STA_MASK ; 
 int /*<<< orphan*/  COMMON_INT_MASK_1 ; 
 int /*<<< orphan*/  COMMON_INT_MASK_2 ; 
 int /*<<< orphan*/  COMMON_INT_MASK_3 ; 
 int /*<<< orphan*/  COMMON_INT_MASK_4 ; 
 int /*<<< orphan*/  INT_STA_MASK ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

void analogix_dp_config_interrupt(struct analogix_dp_device *dp)
{
	u32 reg;

	/* 0: mask, 1: unmask */
	reg = COMMON_INT_MASK_1;
	writel(reg, dp->reg_base + ANALOGIX_DP_COMMON_INT_MASK_1);

	reg = COMMON_INT_MASK_2;
	writel(reg, dp->reg_base + ANALOGIX_DP_COMMON_INT_MASK_2);

	reg = COMMON_INT_MASK_3;
	writel(reg, dp->reg_base + ANALOGIX_DP_COMMON_INT_MASK_3);

	reg = COMMON_INT_MASK_4;
	writel(reg, dp->reg_base + ANALOGIX_DP_COMMON_INT_MASK_4);

	reg = INT_STA_MASK;
	writel(reg, dp->reg_base + ANALOGIX_DP_INT_STA_MASK);
}