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
struct task_status_struct {int /*<<< orphan*/  stat; int /*<<< orphan*/  resp; } ;
struct sas_task {int task_state_flags; scalar_t__ task_proto; int /*<<< orphan*/  task_state_lock; struct task_status_struct task_status; } ;
struct hisi_sas_slot {int /*<<< orphan*/  is_internal; } ;
struct hisi_hba {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SAS_ABORTED_TASK ; 
 scalar_t__ SAS_PROTOCOL_SMP ; 
 int SAS_TASK_AT_INITIATOR ; 
 int /*<<< orphan*/  SAS_TASK_COMPLETE ; 
 int SAS_TASK_STATE_DONE ; 
 int SAS_TASK_STATE_PENDING ; 
 int /*<<< orphan*/  hisi_sas_slot_task_free (struct hisi_hba*,struct sas_task*,struct hisi_sas_slot*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void hisi_sas_do_release_task(struct hisi_hba *hisi_hba, struct sas_task *task,
				     struct hisi_sas_slot *slot)
{
	if (task) {
		unsigned long flags;
		struct task_status_struct *ts;

		ts = &task->task_status;

		ts->resp = SAS_TASK_COMPLETE;
		ts->stat = SAS_ABORTED_TASK;
		spin_lock_irqsave(&task->task_state_lock, flags);
		task->task_state_flags &=
			~(SAS_TASK_STATE_PENDING | SAS_TASK_AT_INITIATOR);
		if (!slot->is_internal && task->task_proto != SAS_PROTOCOL_SMP)
			task->task_state_flags |= SAS_TASK_STATE_DONE;
		spin_unlock_irqrestore(&task->task_state_lock, flags);
	}

	hisi_sas_slot_task_free(hisi_hba, task, slot);
}