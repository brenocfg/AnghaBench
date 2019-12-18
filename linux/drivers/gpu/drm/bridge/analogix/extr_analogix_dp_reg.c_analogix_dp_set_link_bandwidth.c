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
typedef  scalar_t__ u32 ;
struct analogix_dp_device {scalar_t__ reg_base; } ;

/* Variables and functions */
 scalar_t__ ANALOGIX_DP_LINK_BW_SET ; 
 scalar_t__ DP_LINK_BW_1_62 ; 
 scalar_t__ DP_LINK_BW_2_7 ; 
 int /*<<< orphan*/  writel (scalar_t__,scalar_t__) ; 

void analogix_dp_set_link_bandwidth(struct analogix_dp_device *dp, u32 bwtype)
{
	u32 reg;

	reg = bwtype;
	if ((bwtype == DP_LINK_BW_2_7) || (bwtype == DP_LINK_BW_1_62))
		writel(reg, dp->reg_base + ANALOGIX_DP_LINK_BW_SET);
}