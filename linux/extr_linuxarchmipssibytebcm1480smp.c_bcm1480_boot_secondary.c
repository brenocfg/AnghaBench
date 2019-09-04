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
struct task_struct {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  __KSTK_TOS (struct task_struct*) ; 
 int cfe_cpu_start (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_logical_map (int) ; 
 int /*<<< orphan*/  printk (char*,int,int) ; 
 int /*<<< orphan*/  smp_bootstrap ; 
 scalar_t__ task_thread_info (struct task_struct*) ; 

__attribute__((used)) static int bcm1480_boot_secondary(int cpu, struct task_struct *idle)
{
	int retval;

	retval = cfe_cpu_start(cpu_logical_map(cpu), &smp_bootstrap,
			       __KSTK_TOS(idle),
			       (unsigned long)task_thread_info(idle), 0);
	if (retval != 0)
		printk("cfe_start_cpu(%i) returned %i\n" , cpu, retval);
	return retval;
}