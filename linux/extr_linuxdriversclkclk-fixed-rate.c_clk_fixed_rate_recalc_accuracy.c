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
struct clk_hw {int dummy; } ;
struct TYPE_2__ {unsigned long fixed_accuracy; } ;

/* Variables and functions */
 TYPE_1__* to_clk_fixed_rate (struct clk_hw*) ; 

__attribute__((used)) static unsigned long clk_fixed_rate_recalc_accuracy(struct clk_hw *hw,
		unsigned long parent_accuracy)
{
	return to_clk_fixed_rate(hw)->fixed_accuracy;
}