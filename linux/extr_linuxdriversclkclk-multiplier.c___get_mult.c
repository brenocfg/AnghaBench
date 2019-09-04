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
struct clk_multiplier {int flags; } ;

/* Variables and functions */
 int CLK_MULTIPLIER_ROUND_CLOSEST ; 
 unsigned long DIV_ROUND_CLOSEST (unsigned long,unsigned long) ; 

__attribute__((used)) static unsigned long __get_mult(struct clk_multiplier *mult,
				unsigned long rate,
				unsigned long parent_rate)
{
	if (mult->flags & CLK_MULTIPLIER_ROUND_CLOSEST)
		return DIV_ROUND_CLOSEST(rate, parent_rate);

	return rate / parent_rate;
}