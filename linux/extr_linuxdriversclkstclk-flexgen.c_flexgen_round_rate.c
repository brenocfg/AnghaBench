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
struct clk_hw {int dummy; } ;

/* Variables and functions */
 int CLK_SET_RATE_PARENT ; 
 unsigned long clk_best_div (unsigned long,unsigned long) ; 
 int clk_hw_get_flags (struct clk_hw*) ; 

__attribute__((used)) static long flexgen_round_rate(struct clk_hw *hw, unsigned long rate,
				   unsigned long *prate)
{
	unsigned long div;

	/* Round div according to exact prate and wished rate */
	div = clk_best_div(*prate, rate);

	if (clk_hw_get_flags(hw) & CLK_SET_RATE_PARENT) {
		*prate = rate * div;
		return rate;
	}

	return *prate / div;
}