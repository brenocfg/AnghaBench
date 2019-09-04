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
typedef  int /*<<< orphan*/  u64 ;
struct clk_hw {int dummy; } ;
struct clk_div_table {int dummy; } ;

/* Variables and functions */
 unsigned long CLK_DIVIDER_ALLOW_ZERO ; 
 unsigned long DIV_ROUND_UP_ULL (int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  WARN (int,char*,int /*<<< orphan*/ ) ; 
 unsigned int _get_div (struct clk_div_table const*,unsigned int,unsigned long,unsigned long) ; 
 int /*<<< orphan*/  clk_hw_get_name (struct clk_hw*) ; 

unsigned long divider_recalc_rate(struct clk_hw *hw, unsigned long parent_rate,
				  unsigned int val,
				  const struct clk_div_table *table,
				  unsigned long flags, unsigned long width)
{
	unsigned int div;

	div = _get_div(table, val, flags, width);
	if (!div) {
		WARN(!(flags & CLK_DIVIDER_ALLOW_ZERO),
			"%s: Zero divisor and CLK_DIVIDER_ALLOW_ZERO not set\n",
			clk_hw_get_name(hw));
		return parent_rate;
	}

	return DIV_ROUND_UP_ULL((u64)parent_rate, div);
}