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
struct sas_task {int task_state_flags; int /*<<< orphan*/  task_state_lock; struct asd_ascb* lldd_task; } ;
struct asd_ascb {int /*<<< orphan*/ * completion; scalar_t__ tag_valid; } ;

/* Variables and functions */
 int /*<<< orphan*/  AIC94XX_SCB_TIMEOUT ; 
 int /*<<< orphan*/  ASD_DPRINTK (char*) ; 
 int /*<<< orphan*/  DECLARE_COMPLETION_ONSTACK (int /*<<< orphan*/ ) ; 
 int SAS_TASK_STATE_DONE ; 
 int TMF_RESP_FUNC_COMPLETE ; 
 int TMF_RESP_FUNC_FAILED ; 
 int asd_clear_nexus_index (struct sas_task*) ; 
 int asd_clear_nexus_tag (struct sas_task*) ; 
 int /*<<< orphan*/  completion ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int wait_for_completion_timeout (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int asd_clear_nexus(struct sas_task *task)
{
	int res = TMF_RESP_FUNC_FAILED;
	int leftover;
	struct asd_ascb *tascb = task->lldd_task;
	DECLARE_COMPLETION_ONSTACK(completion);
	unsigned long flags;

	tascb->completion = &completion;

	ASD_DPRINTK("task not done, clearing nexus\n");
	if (tascb->tag_valid)
		res = asd_clear_nexus_tag(task);
	else
		res = asd_clear_nexus_index(task);
	leftover = wait_for_completion_timeout(&completion,
					       AIC94XX_SCB_TIMEOUT);
	tascb->completion = NULL;
	ASD_DPRINTK("came back from clear nexus\n");
	spin_lock_irqsave(&task->task_state_lock, flags);
	if (leftover < 1)
		res = TMF_RESP_FUNC_FAILED;
	if (task->task_state_flags & SAS_TASK_STATE_DONE)
		res = TMF_RESP_FUNC_COMPLETE;
	spin_unlock_irqrestore(&task->task_state_lock, flags);

	return res;
}