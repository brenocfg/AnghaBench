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
struct cpu_clk {int cpu; scalar_t__ reg_base; } ;
struct clk_hw {int dummy; } ;

/* Variables and functions */
 int SYS_CTRL_CLK_DIVIDER_MASK ; 
 scalar_t__ SYS_CTRL_CLK_DIVIDER_VALUE_OFFSET ; 
 int readl (scalar_t__) ; 
 struct cpu_clk* to_cpu_clk (struct clk_hw*) ; 

__attribute__((used)) static unsigned long clk_cpu_recalc_rate(struct clk_hw *hwclk,
					 unsigned long parent_rate)
{
	struct cpu_clk *cpuclk = to_cpu_clk(hwclk);
	u32 reg, div;

	reg = readl(cpuclk->reg_base + SYS_CTRL_CLK_DIVIDER_VALUE_OFFSET);
	div = (reg >> (cpuclk->cpu * 8)) & SYS_CTRL_CLK_DIVIDER_MASK;
	return parent_rate / div;
}