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
struct vf610_dac {scalar_t__ regs; } ;

/* Variables and functions */
 int VF610_DAC_DACEN ; 
 scalar_t__ VF610_DACx_STATCTRL ; 
 int readl (scalar_t__) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static void vf610_dac_exit(struct vf610_dac *info)
{
	int val;

	val = readl(info->regs + VF610_DACx_STATCTRL);
	val &= ~VF610_DAC_DACEN;
	writel(val, info->regs + VF610_DACx_STATCTRL);
}