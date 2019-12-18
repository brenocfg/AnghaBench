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
struct iscsi_cmd {int dataout_timer_flags; int /*<<< orphan*/  dataout_timeout_lock; int /*<<< orphan*/  init_task_tag; int /*<<< orphan*/  dataout_timer; } ;

/* Variables and functions */
 int ISCSI_TF_RUNNING ; 
 int ISCSI_TF_STOP ; 
 int /*<<< orphan*/  del_timer_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

void iscsit_stop_dataout_timer(struct iscsi_cmd *cmd)
{
	spin_lock_bh(&cmd->dataout_timeout_lock);
	if (!(cmd->dataout_timer_flags & ISCSI_TF_RUNNING)) {
		spin_unlock_bh(&cmd->dataout_timeout_lock);
		return;
	}
	cmd->dataout_timer_flags |= ISCSI_TF_STOP;
	spin_unlock_bh(&cmd->dataout_timeout_lock);

	del_timer_sync(&cmd->dataout_timer);

	spin_lock_bh(&cmd->dataout_timeout_lock);
	cmd->dataout_timer_flags &= ~ISCSI_TF_RUNNING;
	pr_debug("Stopped DataOUT Timer for ITT: 0x%08x\n",
			cmd->init_task_tag);
	spin_unlock_bh(&cmd->dataout_timeout_lock);
}