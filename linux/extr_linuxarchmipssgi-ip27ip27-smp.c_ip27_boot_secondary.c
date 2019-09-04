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
typedef  int /*<<< orphan*/  launch_proc_t ;

/* Variables and functions */
 int /*<<< orphan*/  LAUNCH_SLAVE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,void*) ; 
 scalar_t__ MAPPED_KERN_RW_TO_K0 (int /*<<< orphan*/ ) ; 
 unsigned long __KSTK_TOS (struct task_struct*) ; 
 int /*<<< orphan*/  cputonasid (int) ; 
 int /*<<< orphan*/  cputoslice (int) ; 
 int /*<<< orphan*/  smp_bootstrap ; 
 scalar_t__ task_thread_info (struct task_struct*) ; 

__attribute__((used)) static int ip27_boot_secondary(int cpu, struct task_struct *idle)
{
	unsigned long gp = (unsigned long)task_thread_info(idle);
	unsigned long sp = __KSTK_TOS(idle);

	LAUNCH_SLAVE(cputonasid(cpu), cputoslice(cpu),
		(launch_proc_t)MAPPED_KERN_RW_TO_K0(smp_bootstrap),
		0, (void *) sp, (void *) gp);
	return 0;
}