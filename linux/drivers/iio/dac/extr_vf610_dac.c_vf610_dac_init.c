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
struct vf610_dac {scalar_t__ regs; int /*<<< orphan*/  conv_mode; } ;

/* Variables and functions */
 int /*<<< orphan*/  VF610_DAC_CONV_LOW_POWER ; 
 int VF610_DAC_DACEN ; 
 int VF610_DAC_DACRFS ; 
 int VF610_DAC_LPEN ; 
 scalar_t__ VF610_DACx_STATCTRL ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static void vf610_dac_init(struct vf610_dac *info)
{
	int val;

	info->conv_mode = VF610_DAC_CONV_LOW_POWER;
	val = VF610_DAC_DACEN | VF610_DAC_DACRFS |
		VF610_DAC_LPEN;
	writel(val, info->regs + VF610_DACx_STATCTRL);
}