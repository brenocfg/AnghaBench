#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */

/* Variables and functions */
 int /*<<< orphan*/  atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  local_irq_disable () ; 
 int /*<<< orphan*/  local_irq_enable () ; 
 int /*<<< orphan*/  num_events ; 
 int /*<<< orphan*/  setup_pmc_cpu (int*) ; 

__attribute__((used)) static int cpusf_pmu_setup(unsigned int cpu, int flags)
{
	/* Ignore the notification if no events are scheduled on the PMU.
	 * This might be racy...
	 */
	if (!atomic_read(&num_events))
		return 0;

	local_irq_disable();
	setup_pmc_cpu(&flags);
	local_irq_enable();
	return 0;
}