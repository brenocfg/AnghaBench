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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u64 ;
struct clk_hw {int dummy; } ;
struct clk_div_table {int dummy; } ;

/* Variables and functions */
 long DIV_ROUND_UP_ULL (int /*<<< orphan*/ ,int) ; 
 int clk_divider_bestdiv (struct clk_hw*,struct clk_hw*,unsigned long,unsigned long*,struct clk_div_table const*,int /*<<< orphan*/ ,unsigned long) ; 

long divider_round_rate_parent(struct clk_hw *hw, struct clk_hw *parent,
			       unsigned long rate, unsigned long *prate,
			       const struct clk_div_table *table,
			       u8 width, unsigned long flags)
{
	int div;

	div = clk_divider_bestdiv(hw, parent, rate, prate, table, width, flags);

	return DIV_ROUND_UP_ULL((u64)*prate, div);
}