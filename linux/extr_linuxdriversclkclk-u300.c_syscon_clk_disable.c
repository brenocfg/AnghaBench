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
struct clk_syscon {int clk_val; scalar_t__ hw_ctrld; } ;
struct clk_hw {int dummy; } ;

/* Variables and functions */
 scalar_t__ U300_SYSCON_SBCDR ; 
 int U300_SYSCON_SBCER_UART_CLK_EN ; 
 scalar_t__ syscon_vbase ; 
 struct clk_syscon* to_syscon (struct clk_hw*) ; 
 int /*<<< orphan*/  writew (int,scalar_t__) ; 

__attribute__((used)) static void syscon_clk_disable(struct clk_hw *hw)
{
	struct clk_syscon *sclk = to_syscon(hw);

	/* Don't touch the hardware controlled clocks */
	if (sclk->hw_ctrld)
		return;
	if (sclk->clk_val == 0xFFFFU)
		return;
	/* Please don't disable the console port */
	if (sclk->clk_val == U300_SYSCON_SBCER_UART_CLK_EN)
		return;

	writew(sclk->clk_val, syscon_vbase + U300_SYSCON_SBCDR);
}