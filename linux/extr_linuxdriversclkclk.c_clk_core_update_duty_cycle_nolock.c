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
struct clk_duty {scalar_t__ den; scalar_t__ num; } ;
struct clk_core {int /*<<< orphan*/  hw; TYPE_1__* ops; struct clk_duty duty; } ;
struct TYPE_2__ {int (* get_duty_cycle ) (int /*<<< orphan*/ ,struct clk_duty*) ;} ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  clk_core_reset_duty_cycle_nolock (struct clk_core*) ; 
 int clk_core_update_duty_cycle_parent_nolock (struct clk_core*) ; 
 int stub1 (int /*<<< orphan*/ ,struct clk_duty*) ; 

__attribute__((used)) static int clk_core_update_duty_cycle_nolock(struct clk_core *core)
{
	struct clk_duty *duty = &core->duty;
	int ret = 0;

	if (!core->ops->get_duty_cycle)
		return clk_core_update_duty_cycle_parent_nolock(core);

	ret = core->ops->get_duty_cycle(core->hw, duty);
	if (ret)
		goto reset;

	/* Don't trust the clock provider too much */
	if (duty->den == 0 || duty->num > duty->den) {
		ret = -EINVAL;
		goto reset;
	}

	return 0;

reset:
	clk_core_reset_duty_cycle_nolock(core);
	return ret;
}