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
struct clk_omap_divider {int flags; scalar_t__ table; } ;

/* Variables and functions */
 int CLK_DIVIDER_POWER_OF_TWO ; 
 int _is_valid_table_div (scalar_t__,unsigned int) ; 
 int is_power_of_2 (unsigned int) ; 

__attribute__((used)) static bool _is_valid_div(struct clk_omap_divider *divider, unsigned int div)
{
	if (divider->flags & CLK_DIVIDER_POWER_OF_TWO)
		return is_power_of_2(div);
	if (divider->table)
		return _is_valid_table_div(divider->table, div);
	return true;
}