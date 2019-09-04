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
struct rdt_resource {int dummy; } ;
struct rdt_domain {int cqm_work_cpu; int /*<<< orphan*/  cqm_limbo; int /*<<< orphan*/  cpu_mask; } ;

/* Variables and functions */
 size_t RDT_RESOURCE_L3 ; 
 int cpumask_any (int /*<<< orphan*/ *) ; 
 unsigned long msecs_to_jiffies (unsigned long) ; 
 struct rdt_resource* rdt_resources_all ; 
 int /*<<< orphan*/  schedule_delayed_work_on (int,int /*<<< orphan*/ *,unsigned long) ; 

void cqm_setup_limbo_handler(struct rdt_domain *dom, unsigned long delay_ms)
{
	unsigned long delay = msecs_to_jiffies(delay_ms);
	struct rdt_resource *r;
	int cpu;

	r = &rdt_resources_all[RDT_RESOURCE_L3];

	cpu = cpumask_any(&dom->cpu_mask);
	dom->cqm_work_cpu = cpu;

	schedule_delayed_work_on(cpu, &dom->cqm_limbo, delay);
}