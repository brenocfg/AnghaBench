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
struct clk_hw {TYPE_1__* core; } ;
struct TYPE_2__ {unsigned long min_rate; unsigned long max_rate; } ;

/* Variables and functions */

void clk_hw_set_rate_range(struct clk_hw *hw, unsigned long min_rate,
			   unsigned long max_rate)
{
	hw->core->min_rate = min_rate;
	hw->core->max_rate = max_rate;
}