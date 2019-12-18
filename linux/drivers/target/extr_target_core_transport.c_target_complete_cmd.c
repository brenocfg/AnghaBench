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
typedef  int u8 ;
struct se_cmd {int scsi_status; int se_cmd_flags; int transport_state; int /*<<< orphan*/  work; int /*<<< orphan*/  cpuid; int /*<<< orphan*/  t_state_lock; int /*<<< orphan*/  t_state; } ;

/* Variables and functions */
 int CMD_T_ACTIVE ; 
 int CMD_T_COMPLETE ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
#define  SAM_STAT_CHECK_CONDITION 128 
 int SCF_TRANSPORT_TASK_SENSE ; 
 int SCF_USE_CPUID ; 
 int /*<<< orphan*/  TRANSPORT_COMPLETE ; 
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  queue_work_on (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 scalar_t__ target_cmd_interrupted (struct se_cmd*) ; 
 int /*<<< orphan*/  target_complete_failure_work ; 
 int /*<<< orphan*/  target_complete_ok_work ; 
 int /*<<< orphan*/  target_completion_wq ; 

void target_complete_cmd(struct se_cmd *cmd, u8 scsi_status)
{
	int success;
	unsigned long flags;

	if (target_cmd_interrupted(cmd))
		return;

	cmd->scsi_status = scsi_status;

	spin_lock_irqsave(&cmd->t_state_lock, flags);
	switch (cmd->scsi_status) {
	case SAM_STAT_CHECK_CONDITION:
		if (cmd->se_cmd_flags & SCF_TRANSPORT_TASK_SENSE)
			success = 1;
		else
			success = 0;
		break;
	default:
		success = 1;
		break;
	}

	cmd->t_state = TRANSPORT_COMPLETE;
	cmd->transport_state |= (CMD_T_COMPLETE | CMD_T_ACTIVE);
	spin_unlock_irqrestore(&cmd->t_state_lock, flags);

	INIT_WORK(&cmd->work, success ? target_complete_ok_work :
		  target_complete_failure_work);
	if (cmd->se_cmd_flags & SCF_USE_CPUID)
		queue_work_on(cmd->cpuid, target_completion_wq, &cmd->work);
	else
		queue_work(target_completion_wq, &cmd->work);
}