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
struct clk_div_table {int dummy; } ;

/* Variables and functions */
 unsigned long CLK_DIVIDER_ONE_BASED ; 
 unsigned long CLK_DIVIDER_POWER_OF_TWO ; 
 unsigned int _get_table_maxdiv (struct clk_div_table const*,int /*<<< orphan*/ ) ; 
 int clk_div_mask (int /*<<< orphan*/ ) ; 

__attribute__((used)) static unsigned int _get_maxdiv(const struct clk_div_table *table, u8 width,
				unsigned long flags)
{
	if (flags & CLK_DIVIDER_ONE_BASED)
		return clk_div_mask(width);
	if (flags & CLK_DIVIDER_POWER_OF_TWO)
		return 1 << clk_div_mask(width);
	if (table)
		return _get_table_maxdiv(table, width);
	return clk_div_mask(width) + 1;
}