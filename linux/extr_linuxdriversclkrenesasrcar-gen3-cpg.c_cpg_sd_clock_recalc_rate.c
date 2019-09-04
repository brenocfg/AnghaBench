#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct sd_clock {size_t cur_div_idx; TYPE_1__* div_table; } ;
struct clk_hw {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  div; } ;

/* Variables and functions */
 unsigned long DIV_ROUND_CLOSEST (unsigned long,int /*<<< orphan*/ ) ; 
 struct sd_clock* to_sd_clock (struct clk_hw*) ; 

__attribute__((used)) static unsigned long cpg_sd_clock_recalc_rate(struct clk_hw *hw,
						unsigned long parent_rate)
{
	struct sd_clock *clock = to_sd_clock(hw);

	return DIV_ROUND_CLOSEST(parent_rate,
				 clock->div_table[clock->cur_div_idx].div);
}