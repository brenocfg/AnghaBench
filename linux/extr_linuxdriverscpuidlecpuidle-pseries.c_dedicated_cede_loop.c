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
struct cpuidle_driver {int dummy; } ;
struct cpuidle_device {int dummy; } ;
struct TYPE_2__ {int donate_dedicated_cpu; } ;

/* Variables and functions */
 int /*<<< orphan*/  HMT_medium () ; 
 int /*<<< orphan*/  check_and_cede_processor () ; 
 TYPE_1__* get_lppaca () ; 
 int /*<<< orphan*/  idle_loop_epilog (unsigned long) ; 
 int /*<<< orphan*/  idle_loop_prolog (unsigned long*) ; 
 int /*<<< orphan*/  local_irq_disable () ; 

__attribute__((used)) static int dedicated_cede_loop(struct cpuidle_device *dev,
				struct cpuidle_driver *drv,
				int index)
{
	unsigned long in_purr;

	idle_loop_prolog(&in_purr);
	get_lppaca()->donate_dedicated_cpu = 1;

	HMT_medium();
	check_and_cede_processor();

	local_irq_disable();
	get_lppaca()->donate_dedicated_cpu = 0;

	idle_loop_epilog(in_purr);

	return index;
}