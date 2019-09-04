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
 scalar_t__ ANALOGIX_DP_LN2_LINK_TRAINING_CTL ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

void analogix_dp_set_lane2_link_training(struct analogix_dp_device *dp,
					 u32 training_lane)
{
	u32 reg;

	reg = training_lane;
	writel(reg, dp->reg_base + ANALOGIX_DP_LN2_LINK_TRAINING_CTL);
}