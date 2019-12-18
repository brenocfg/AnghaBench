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
struct workqueue_struct {int dummy; } ;
struct megasas_instance {int /*<<< orphan*/  fw_fault_work; struct workqueue_struct* fw_fault_work_q; } ;

/* Variables and functions */
 int /*<<< orphan*/  cancel_delayed_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  destroy_workqueue (struct workqueue_struct*) ; 
 int /*<<< orphan*/  flush_workqueue (struct workqueue_struct*) ; 

void
megasas_fusion_stop_watchdog(struct megasas_instance *instance)
{
	struct workqueue_struct *wq;

	if (instance->fw_fault_work_q) {
		wq = instance->fw_fault_work_q;
		instance->fw_fault_work_q = NULL;
		if (!cancel_delayed_work_sync(&instance->fw_fault_work))
			flush_workqueue(wq);
		destroy_workqueue(wq);
	}
}