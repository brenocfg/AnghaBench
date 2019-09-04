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
struct rdt_domain {int mbm_work_cpu; int /*<<< orphan*/  mbm_over; int /*<<< orphan*/  cpu_mask; } ;

/* Variables and functions */
 int cpumask_any (int /*<<< orphan*/ *) ; 
 unsigned long msecs_to_jiffies (unsigned long) ; 
 int /*<<< orphan*/  rdt_enable_key ; 
 int /*<<< orphan*/  schedule_delayed_work_on (int,int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  static_branch_likely (int /*<<< orphan*/ *) ; 

void mbm_setup_overflow_handler(struct rdt_domain *dom, unsigned long delay_ms)
{
	unsigned long delay = msecs_to_jiffies(delay_ms);
	int cpu;

	if (!static_branch_likely(&rdt_enable_key))
		return;
	cpu = cpumask_any(&dom->cpu_mask);
	dom->mbm_work_cpu = cpu;
	schedule_delayed_work_on(cpu, &dom->mbm_over, delay);
}