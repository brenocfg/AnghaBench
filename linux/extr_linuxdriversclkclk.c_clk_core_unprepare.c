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
struct clk_core {int prepare_count; int flags; scalar_t__ enable_count; struct clk_core* parent; int /*<<< orphan*/  hw; TYPE_1__* ops; int /*<<< orphan*/  name; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* unprepare ) (int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int CLK_IS_CRITICAL ; 
 int CLK_SET_RATE_GATE ; 
 scalar_t__ WARN (int,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clk_core_rate_unprotect (struct clk_core*) ; 
 int /*<<< orphan*/  clk_pm_runtime_put (struct clk_core*) ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  prepare_lock ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trace_clk_unprepare (struct clk_core*) ; 
 int /*<<< orphan*/  trace_clk_unprepare_complete (struct clk_core*) ; 

__attribute__((used)) static void clk_core_unprepare(struct clk_core *core)
{
	lockdep_assert_held(&prepare_lock);

	if (!core)
		return;

	if (WARN(core->prepare_count == 0,
	    "%s already unprepared\n", core->name))
		return;

	if (WARN(core->prepare_count == 1 && core->flags & CLK_IS_CRITICAL,
	    "Unpreparing critical %s\n", core->name))
		return;

	if (core->flags & CLK_SET_RATE_GATE)
		clk_core_rate_unprotect(core);

	if (--core->prepare_count > 0)
		return;

	WARN(core->enable_count > 0, "Unpreparing enabled %s\n", core->name);

	trace_clk_unprepare(core);

	if (core->ops->unprepare)
		core->ops->unprepare(core->hw);

	clk_pm_runtime_put(core);

	trace_clk_unprepare_complete(core);
	clk_core_unprepare(core->parent);
}