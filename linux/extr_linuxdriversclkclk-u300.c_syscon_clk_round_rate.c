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
struct clk_syscon {scalar_t__ clk_val; } ;
struct clk_hw {int dummy; } ;

/* Variables and functions */
 scalar_t__ U300_SYSCON_SBCER_CPU_CLK_EN ; 
 struct clk_syscon* to_syscon (struct clk_hw*) ; 

__attribute__((used)) static long
syscon_clk_round_rate(struct clk_hw *hw, unsigned long rate,
		      unsigned long *prate)
{
	struct clk_syscon *sclk = to_syscon(hw);

	if (sclk->clk_val != U300_SYSCON_SBCER_CPU_CLK_EN)
		return *prate;
	/* We really only support setting the rate of the CPU clock */
	if (rate <= 13000000)
		return 13000000;
	if (rate <= 52000000)
		return 52000000;
	if (rate <= 104000000)
		return 104000000;
	return 208000000;
}