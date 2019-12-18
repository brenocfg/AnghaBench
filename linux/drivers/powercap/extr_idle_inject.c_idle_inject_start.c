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
struct idle_inject_device {int /*<<< orphan*/  timer; int /*<<< orphan*/  cpumask; int /*<<< orphan*/  run_duration_us; int /*<<< orphan*/  idle_duration_us; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  HRTIMER_MODE_REL ; 
 unsigned int NSEC_PER_USEC ; 
 unsigned int READ_ONCE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpumask_pr_args (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hrtimer_start (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  idle_inject_wakeup (struct idle_inject_device*) ; 
 int /*<<< orphan*/  ns_to_ktime (unsigned int) ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  to_cpumask (int /*<<< orphan*/ ) ; 

int idle_inject_start(struct idle_inject_device *ii_dev)
{
	unsigned int idle_duration_us = READ_ONCE(ii_dev->idle_duration_us);
	unsigned int run_duration_us = READ_ONCE(ii_dev->run_duration_us);

	if (!idle_duration_us || !run_duration_us)
		return -EINVAL;

	pr_debug("Starting injecting idle cycles on CPUs '%*pbl'\n",
		 cpumask_pr_args(to_cpumask(ii_dev->cpumask)));

	idle_inject_wakeup(ii_dev);

	hrtimer_start(&ii_dev->timer,
		      ns_to_ktime((idle_duration_us + run_duration_us) *
				  NSEC_PER_USEC),
		      HRTIMER_MODE_REL);

	return 0;
}