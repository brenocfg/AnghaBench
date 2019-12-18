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
struct analogix_dp_device {scalar_t__ reg_base; scalar_t__ hpd_gpiod; } ;

/* Variables and functions */
 scalar_t__ ANALOGIX_DP_SYS_CTL_3 ; 
 int F_HPD ; 
 int HPD_CTRL ; 
 int /*<<< orphan*/  analogix_dp_clear_hotplug_interrupts (struct analogix_dp_device*) ; 
 int readl (scalar_t__) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

void analogix_dp_init_hpd(struct analogix_dp_device *dp)
{
	u32 reg;

	if (dp->hpd_gpiod)
		return;

	analogix_dp_clear_hotplug_interrupts(dp);

	reg = readl(dp->reg_base + ANALOGIX_DP_SYS_CTL_3);
	reg &= ~(F_HPD | HPD_CTRL);
	writel(reg, dp->reg_base + ANALOGIX_DP_SYS_CTL_3);
}