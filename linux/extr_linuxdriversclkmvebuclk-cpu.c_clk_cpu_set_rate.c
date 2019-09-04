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
struct clk_hw {int /*<<< orphan*/  clk; } ;

/* Variables and functions */
 scalar_t__ __clk_is_enabled (int /*<<< orphan*/ ) ; 
 int clk_cpu_off_set_rate (struct clk_hw*,unsigned long,unsigned long) ; 
 int clk_cpu_on_set_rate (struct clk_hw*,unsigned long,unsigned long) ; 

__attribute__((used)) static int clk_cpu_set_rate(struct clk_hw *hwclk, unsigned long rate,
			    unsigned long parent_rate)
{
	if (__clk_is_enabled(hwclk->clk))
		return clk_cpu_on_set_rate(hwclk, rate, parent_rate);
	else
		return clk_cpu_off_set_rate(hwclk, rate, parent_rate);
}