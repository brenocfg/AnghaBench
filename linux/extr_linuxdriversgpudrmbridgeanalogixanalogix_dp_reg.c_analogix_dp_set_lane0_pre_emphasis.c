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
 scalar_t__ ANALOGIX_DP_LN0_LINK_TRAINING_CTL ; 
 int PRE_EMPHASIS_SET_MASK ; 
 int PRE_EMPHASIS_SET_SHIFT ; 
 int readl (scalar_t__) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

void analogix_dp_set_lane0_pre_emphasis(struct analogix_dp_device *dp,
					u32 level)
{
	u32 reg;

	reg = readl(dp->reg_base + ANALOGIX_DP_LN0_LINK_TRAINING_CTL);
	reg &= ~PRE_EMPHASIS_SET_MASK;
	reg |= level << PRE_EMPHASIS_SET_SHIFT;
	writel(reg, dp->reg_base + ANALOGIX_DP_LN0_LINK_TRAINING_CTL);
}