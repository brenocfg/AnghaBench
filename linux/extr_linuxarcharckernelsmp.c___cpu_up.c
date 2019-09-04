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
struct task_struct {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* cpu_kick ) (unsigned int,unsigned long) ;} ;

/* Variables and functions */
 unsigned long HZ ; 
 int /*<<< orphan*/  arc_default_smp_cpu_kick (unsigned int,unsigned long) ; 
 scalar_t__ cpu_online (unsigned int) ; 
 scalar_t__ first_lines_of_secondary ; 
 unsigned long jiffies ; 
 TYPE_1__ plat_smp_ops ; 
 int /*<<< orphan*/  pr_info (char*,unsigned int,...) ; 
 struct task_struct* secondary_idle_tsk ; 
 int /*<<< orphan*/  stub1 (unsigned int,unsigned long) ; 
 scalar_t__ time_before (unsigned long,unsigned long) ; 

int __cpu_up(unsigned int cpu, struct task_struct *idle)
{
	unsigned long wait_till;

	secondary_idle_tsk = idle;

	pr_info("Idle Task [%d] %p", cpu, idle);
	pr_info("Trying to bring up CPU%u ...\n", cpu);

	if (plat_smp_ops.cpu_kick)
		plat_smp_ops.cpu_kick(cpu,
				(unsigned long)first_lines_of_secondary);
	else
		arc_default_smp_cpu_kick(cpu, (unsigned long)NULL);

	/* wait for 1 sec after kicking the secondary */
	wait_till = jiffies + HZ;
	while (time_before(jiffies, wait_till)) {
		if (cpu_online(cpu))
			break;
	}

	if (!cpu_online(cpu)) {
		pr_info("Timeout: CPU%u FAILED to comeup !!!\n", cpu);
		return -1;
	}

	secondary_idle_tsk = NULL;

	return 0;
}