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
typedef  unsigned int u8 ;
struct clk_omap_divider {int flags; scalar_t__ table; } ;

/* Variables and functions */
 int CLK_DIVIDER_ONE_BASED ; 
 int CLK_DIVIDER_POWER_OF_TWO ; 
 unsigned int __ffs (unsigned int) ; 
 unsigned int _get_table_val (scalar_t__,unsigned int) ; 

__attribute__((used)) static unsigned int _get_val(struct clk_omap_divider *divider, u8 div)
{
	if (divider->flags & CLK_DIVIDER_ONE_BASED)
		return div;
	if (divider->flags & CLK_DIVIDER_POWER_OF_TWO)
		return __ffs(div);
	if (divider->table)
		return  _get_table_val(divider->table, div);
	return div - 1;
}