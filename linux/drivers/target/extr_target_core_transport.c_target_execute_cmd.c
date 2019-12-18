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
struct se_cmd {int transport_state; int /*<<< orphan*/  t_state_lock; int /*<<< orphan*/  t_state; } ;

/* Variables and functions */
 int CMD_T_ACTIVE ; 
 int CMD_T_SENT ; 
 int /*<<< orphan*/  TRANSPORT_PROCESSING ; 
 int /*<<< orphan*/  __target_execute_cmd (struct se_cmd*,int) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 scalar_t__ target_cmd_interrupted (struct se_cmd*) ; 
 scalar_t__ target_handle_task_attr (struct se_cmd*) ; 
 scalar_t__ target_write_prot_action (struct se_cmd*) ; 

void target_execute_cmd(struct se_cmd *cmd)
{
	/*
	 * Determine if frontend context caller is requesting the stopping of
	 * this command for frontend exceptions.
	 *
	 * If the received CDB has already been aborted stop processing it here.
	 */
	if (target_cmd_interrupted(cmd))
		return;

	spin_lock_irq(&cmd->t_state_lock);
	cmd->t_state = TRANSPORT_PROCESSING;
	cmd->transport_state |= CMD_T_ACTIVE | CMD_T_SENT;
	spin_unlock_irq(&cmd->t_state_lock);

	if (target_write_prot_action(cmd))
		return;

	if (target_handle_task_attr(cmd)) {
		spin_lock_irq(&cmd->t_state_lock);
		cmd->transport_state &= ~CMD_T_SENT;
		spin_unlock_irq(&cmd->t_state_lock);
		return;
	}

	__target_execute_cmd(cmd, true);
}