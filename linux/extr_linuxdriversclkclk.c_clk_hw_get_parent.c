#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct clk_hw {TYPE_2__* core; } ;
struct TYPE_4__ {TYPE_1__* parent; } ;
struct TYPE_3__ {struct clk_hw* hw; } ;

/* Variables and functions */

struct clk_hw *clk_hw_get_parent(const struct clk_hw *hw)
{
	return hw->core->parent ? hw->core->parent->hw : NULL;
}