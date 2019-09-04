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
struct notifier_block {int dummy; } ;

/* Variables and functions */
#define  CPU_CLUSTER_PM_ENTER 129 
#define  CPU_CLUSTER_PM_EXIT 128 
 int NOTIFY_OK ; 
 int /*<<< orphan*/  clkdm_restore_context () ; 
 int /*<<< orphan*/  clkdm_save_context () ; 
 int /*<<< orphan*/  enable_off_mode ; 

__attribute__((used)) static int cpu_notifier(struct notifier_block *nb, unsigned long cmd, void *v)
{
	switch (cmd) {
	case CPU_CLUSTER_PM_ENTER:
		if (enable_off_mode)
			clkdm_save_context();
		break;
	case CPU_CLUSTER_PM_EXIT:
		if (enable_off_mode)
			clkdm_restore_context();
		break;
	}

	return NOTIFY_OK;
}