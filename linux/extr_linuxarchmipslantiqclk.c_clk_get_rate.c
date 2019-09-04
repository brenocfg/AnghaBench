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
struct clk {scalar_t__ rate; unsigned long (* get_rate ) () ;} ;

/* Variables and functions */
 int /*<<< orphan*/  clk_good (struct clk*) ; 
 unsigned long stub1 () ; 
 scalar_t__ unlikely (int) ; 

unsigned long clk_get_rate(struct clk *clk)
{
	if (unlikely(!clk_good(clk)))
		return 0;

	if (clk->rate != 0)
		return clk->rate;

	if (clk->get_rate != NULL)
		return clk->get_rate();

	return 0;
}