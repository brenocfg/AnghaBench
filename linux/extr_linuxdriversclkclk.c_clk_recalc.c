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
struct clk_core {int /*<<< orphan*/  hw; TYPE_1__* ops; } ;
struct TYPE_2__ {unsigned long (* recalc_rate ) (int /*<<< orphan*/ ,unsigned long) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  clk_pm_runtime_get (struct clk_core*) ; 
 int /*<<< orphan*/  clk_pm_runtime_put (struct clk_core*) ; 
 unsigned long stub1 (int /*<<< orphan*/ ,unsigned long) ; 

__attribute__((used)) static unsigned long clk_recalc(struct clk_core *core,
				unsigned long parent_rate)
{
	unsigned long rate = parent_rate;

	if (core->ops->recalc_rate && !clk_pm_runtime_get(core)) {
		rate = core->ops->recalc_rate(core->hw, parent_rate);
		clk_pm_runtime_put(core);
	}
	return rate;
}