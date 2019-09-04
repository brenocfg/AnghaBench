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
struct clk_syscon {scalar_t__ clk_val; int /*<<< orphan*/  reset; } ;
struct clk_hw {int dummy; } ;

/* Variables and functions */
 scalar_t__ U300_SYSCON_SBCER_UART_CLK_EN ; 
 int /*<<< orphan*/  syscon_block_reset_enable (struct clk_syscon*) ; 
 struct clk_syscon* to_syscon (struct clk_hw*) ; 

__attribute__((used)) static void syscon_clk_unprepare(struct clk_hw *hw)
{
	struct clk_syscon *sclk = to_syscon(hw);

	/* Please don't force the console into reset */
	if (sclk->clk_val == U300_SYSCON_SBCER_UART_CLK_EN)
		return;
	/* When unpreparing, force block into reset */
	if (!sclk->reset)
		syscon_block_reset_enable(sclk);
}