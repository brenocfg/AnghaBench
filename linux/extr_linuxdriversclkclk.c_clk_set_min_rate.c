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
struct clk {int /*<<< orphan*/  max_rate; } ;

/* Variables and functions */
 int clk_set_rate_range (struct clk*,unsigned long,int /*<<< orphan*/ ) ; 

int clk_set_min_rate(struct clk *clk, unsigned long rate)
{
	if (!clk)
		return 0;

	return clk_set_rate_range(clk, rate, clk->max_rate);
}