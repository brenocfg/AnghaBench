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
struct clk_bytediv {int /*<<< orphan*/  reg; } ;

/* Variables and functions */
 int pll_read (int /*<<< orphan*/ ) ; 
 struct clk_bytediv* to_clk_bytediv (struct clk_hw*) ; 

__attribute__((used)) static unsigned long clk_bytediv_recalc_rate(struct clk_hw *hw,
		unsigned long parent_rate)
{
	struct clk_bytediv *bytediv = to_clk_bytediv(hw);
	unsigned int div;

	div = pll_read(bytediv->reg) & 0xff;

	return parent_rate / (div + 1);
}