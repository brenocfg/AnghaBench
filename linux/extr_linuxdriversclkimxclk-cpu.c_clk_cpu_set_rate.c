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
struct clk_hw {int dummy; } ;
struct clk_cpu {int /*<<< orphan*/  div; int /*<<< orphan*/  pll; int /*<<< orphan*/  mux; int /*<<< orphan*/  step; } ;

/* Variables and functions */
 int clk_set_parent (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int clk_set_rate (int /*<<< orphan*/ ,unsigned long) ; 
 struct clk_cpu* to_clk_cpu (struct clk_hw*) ; 

__attribute__((used)) static int clk_cpu_set_rate(struct clk_hw *hw, unsigned long rate,
			    unsigned long parent_rate)
{
	struct clk_cpu *cpu = to_clk_cpu(hw);
	int ret;

	/* switch to PLL bypass clock */
	ret = clk_set_parent(cpu->mux, cpu->step);
	if (ret)
		return ret;

	/* reprogram PLL */
	ret = clk_set_rate(cpu->pll, rate);
	if (ret) {
		clk_set_parent(cpu->mux, cpu->pll);
		return ret;
	}
	/* switch back to PLL clock */
	clk_set_parent(cpu->mux, cpu->pll);

	/* Ensure the divider is what we expect */
	clk_set_rate(cpu->div, rate);

	return 0;
}