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
typedef  scalar_t__ u32 ;
struct r9a06g032_clk_div {scalar_t__ min; scalar_t__ max; int table_size; scalar_t__* table; } ;

/* Variables and functions */
 unsigned long DIV_ROUND_UP (unsigned long,unsigned long) ; 

__attribute__((used)) static long
r9a06g032_div_clamp_div(struct r9a06g032_clk_div *clk,
			unsigned long rate, unsigned long prate)
{
	/* + 1 to cope with rates that have the remainder dropped */
	u32 div = DIV_ROUND_UP(prate, rate + 1);
	int i;

	if (div <= clk->min)
		return clk->min;
	if (div >= clk->max)
		return clk->max;

	for (i = 0; clk->table_size && i < clk->table_size - 1; i++) {
		if (div >= clk->table[i] && div <= clk->table[i + 1]) {
			unsigned long m = rate -
				DIV_ROUND_UP(prate, clk->table[i]);
			unsigned long p =
				DIV_ROUND_UP(prate, clk->table[i + 1]) -
				rate;
			/*
			 * select the divider that generates
			 * the value closest to the ideal frequency
			 */
			div = p >= m ? clk->table[i] : clk->table[i + 1];
			return div;
		}
	}
	return div;
}