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
struct clk_prcc {scalar_t__ is_enabled; scalar_t__ base; int /*<<< orphan*/  cg_sel; } ;
struct clk_hw {int dummy; } ;

/* Variables and functions */
 scalar_t__ PRCC_KCKDIS ; 
 struct clk_prcc* to_clk_prcc (struct clk_hw*) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void clk_prcc_kclk_disable(struct clk_hw *hw)
{
	struct clk_prcc *clk = to_clk_prcc(hw);

	writel(clk->cg_sel, (clk->base + PRCC_KCKDIS));
	clk->is_enabled = 0;
}