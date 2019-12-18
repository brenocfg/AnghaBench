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
 scalar_t__ ANALOGIX_DP_LN3_LINK_TRAINING_CTL ; 
 int /*<<< orphan*/  readl (scalar_t__) ; 

u32 analogix_dp_get_lane3_link_training(struct analogix_dp_device *dp)
{
	return readl(dp->reg_base + ANALOGIX_DP_LN3_LINK_TRAINING_CTL);
}