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
struct clk_core {int phase; int /*<<< orphan*/  hw; TYPE_1__* ops; } ;
struct TYPE_2__ {int (* get_phase ) (int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  clk_prepare_lock () ; 
 int /*<<< orphan*/  clk_prepare_unlock () ; 
 int stub1 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int clk_core_get_phase(struct clk_core *core)
{
	int ret;

	clk_prepare_lock();
	/* Always try to update cached phase if possible */
	if (core->ops->get_phase)
		core->phase = core->ops->get_phase(core->hw);
	ret = core->phase;
	clk_prepare_unlock();

	return ret;
}