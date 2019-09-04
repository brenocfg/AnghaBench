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
struct clk_div_table {int div; } ;

/* Variables and functions */
 int INT_MAX ; 

__attribute__((used)) static int _round_up_table(const struct clk_div_table *table, int div)
{
	const struct clk_div_table *clkt;
	int up = INT_MAX;

	for (clkt = table; clkt->div; clkt++) {
		if (clkt->div == div)
			return clkt->div;
		else if (clkt->div < div)
			continue;

		if ((clkt->div - div) < (up - div))
			up = clkt->div;
	}

	return up;
}