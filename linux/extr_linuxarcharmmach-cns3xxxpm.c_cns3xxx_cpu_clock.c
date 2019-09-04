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

/* Variables and functions */
 int /*<<< orphan*/  PM_CLK_CTRL_REG ; 
 int PM_CLK_CTRL_REG_OFFSET_CPU_CLK_DIV ; 
 int PM_CLK_CTRL_REG_OFFSET_PLL_CPU_SEL ; 
 int __raw_readl (int /*<<< orphan*/ ) ; 

int cns3xxx_cpu_clock(void)
{
	u32 reg = __raw_readl(PM_CLK_CTRL_REG);
	int cpu;
	int cpu_sel;
	int div_sel;

	cpu_sel = (reg >> PM_CLK_CTRL_REG_OFFSET_PLL_CPU_SEL) & 0xf;
	div_sel = (reg >> PM_CLK_CTRL_REG_OFFSET_CPU_CLK_DIV) & 0x3;

	cpu = (300 + ((cpu_sel / 3) * 100) + ((cpu_sel % 3) * 33)) >> div_sel;

	return cpu;
}