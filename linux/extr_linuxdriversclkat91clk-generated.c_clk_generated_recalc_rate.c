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
struct clk_generated {scalar_t__ gckdiv; } ;

/* Variables and functions */
 unsigned long DIV_ROUND_CLOSEST (unsigned long,scalar_t__) ; 
 struct clk_generated* to_clk_generated (struct clk_hw*) ; 

__attribute__((used)) static unsigned long
clk_generated_recalc_rate(struct clk_hw *hw,
			  unsigned long parent_rate)
{
	struct clk_generated *gck = to_clk_generated(hw);

	return DIV_ROUND_CLOSEST(parent_rate, gck->gckdiv + 1);
}