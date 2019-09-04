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
struct clk_lookup {int /*<<< orphan*/  clk; scalar_t__ clk_hw; } ;

/* Variables and functions */
 scalar_t__ __clk_get_hw (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __clkdev_add (struct clk_lookup*) ; 

void clkdev_add(struct clk_lookup *cl)
{
	if (!cl->clk_hw)
		cl->clk_hw = __clk_get_hw(cl->clk);
	__clkdev_add(cl);
}