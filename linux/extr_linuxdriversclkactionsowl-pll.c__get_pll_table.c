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
struct clk_pll_table {long rate; } ;

/* Variables and functions */

__attribute__((used)) static const struct clk_pll_table *_get_pll_table(
		const struct clk_pll_table *table, unsigned long rate)
{
	const struct clk_pll_table *clkt;

	for (clkt = table; clkt->rate; clkt++) {
		if (clkt->rate == rate) {
			table = clkt;
			break;
		} else if (clkt->rate < rate)
			table = clkt;
	}

	return table;
}