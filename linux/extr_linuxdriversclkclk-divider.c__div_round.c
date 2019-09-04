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
struct clk_div_table {int dummy; } ;

/* Variables and functions */
 unsigned long CLK_DIVIDER_ROUND_CLOSEST ; 
 int _div_round_closest (struct clk_div_table const*,unsigned long,unsigned long,unsigned long) ; 
 int _div_round_up (struct clk_div_table const*,unsigned long,unsigned long,unsigned long) ; 

__attribute__((used)) static int _div_round(const struct clk_div_table *table,
		      unsigned long parent_rate, unsigned long rate,
		      unsigned long flags)
{
	if (flags & CLK_DIVIDER_ROUND_CLOSEST)
		return _div_round_closest(table, parent_rate, rate, flags);

	return _div_round_up(table, parent_rate, rate, flags);
}