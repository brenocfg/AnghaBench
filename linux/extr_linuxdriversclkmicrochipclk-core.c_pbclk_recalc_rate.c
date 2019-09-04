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
struct pic32_periph_clk {int dummy; } ;
struct clk_hw {int dummy; } ;

/* Variables and functions */
 struct pic32_periph_clk* clkhw_to_pbclk (struct clk_hw*) ; 
 unsigned long pbclk_read_pbdiv (struct pic32_periph_clk*) ; 

__attribute__((used)) static unsigned long pbclk_recalc_rate(struct clk_hw *hw,
				       unsigned long parent_rate)
{
	struct pic32_periph_clk *pb = clkhw_to_pbclk(hw);

	return parent_rate / pbclk_read_pbdiv(pb);
}