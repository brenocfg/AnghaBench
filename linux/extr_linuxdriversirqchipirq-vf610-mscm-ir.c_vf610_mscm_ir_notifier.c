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
#define  CPU_CLUSTER_PM_ENTER 130 
#define  CPU_CLUSTER_PM_ENTER_FAILED 129 
#define  CPU_CLUSTER_PM_EXIT 128 
 int NOTIFY_OK ; 
 int /*<<< orphan*/  mscm_ir_data ; 
 int /*<<< orphan*/  vf610_mscm_ir_restore (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vf610_mscm_ir_save (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int vf610_mscm_ir_notifier(struct notifier_block *self,
				  unsigned long cmd, void *v)
{
	switch (cmd) {
	case CPU_CLUSTER_PM_ENTER:
		vf610_mscm_ir_save(mscm_ir_data);
		break;
	case CPU_CLUSTER_PM_ENTER_FAILED:
	case CPU_CLUSTER_PM_EXIT:
		vf610_mscm_ir_restore(mscm_ir_data);
		break;
	}

	return NOTIFY_OK;
}