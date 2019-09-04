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
struct clk_duty {int dummy; } ;
struct clk_core {int /*<<< orphan*/  duty; int /*<<< orphan*/  hw; TYPE_1__* ops; } ;
struct TYPE_2__ {int (* set_duty_cycle ) (int /*<<< orphan*/ ,struct clk_duty*) ;} ;

/* Variables and functions */
 int EBUSY ; 
 scalar_t__ clk_core_rate_is_protected (struct clk_core*) ; 
 int clk_core_set_duty_cycle_parent_nolock (struct clk_core*,struct clk_duty*) ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,struct clk_duty*,int) ; 
 int /*<<< orphan*/  prepare_lock ; 
 int stub1 (int /*<<< orphan*/ ,struct clk_duty*) ; 
 int /*<<< orphan*/  trace_clk_set_duty_cycle (struct clk_core*,struct clk_duty*) ; 
 int /*<<< orphan*/  trace_clk_set_duty_cycle_complete (struct clk_core*,struct clk_duty*) ; 

__attribute__((used)) static int clk_core_set_duty_cycle_nolock(struct clk_core *core,
					  struct clk_duty *duty)
{
	int ret;

	lockdep_assert_held(&prepare_lock);

	if (clk_core_rate_is_protected(core))
		return -EBUSY;

	trace_clk_set_duty_cycle(core, duty);

	if (!core->ops->set_duty_cycle)
		return clk_core_set_duty_cycle_parent_nolock(core, duty);

	ret = core->ops->set_duty_cycle(core->hw, duty);
	if (!ret)
		memcpy(&core->duty, duty, sizeof(*duty));

	trace_clk_set_duty_cycle_complete(core, duty);

	return ret;
}