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
struct clk_div_table {int div; } ;

/* Variables and functions */
 int DIV_ROUND_UP_ULL (int /*<<< orphan*/ ,unsigned long) ; 
 int INT_MAX ; 

__attribute__((used)) static int _div_round_up(const struct clk_div_table *table,
			 unsigned long parent_rate, unsigned long rate)
{
	const struct clk_div_table *clkt;
	int up = INT_MAX;
	int div = DIV_ROUND_UP_ULL((u64)parent_rate, rate);

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