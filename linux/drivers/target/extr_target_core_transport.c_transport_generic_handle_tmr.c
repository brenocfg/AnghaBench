#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct se_cmd {int transport_state; int /*<<< orphan*/  work; int /*<<< orphan*/  tag; TYPE_1__* se_tmr_req; int /*<<< orphan*/  t_state_lock; int /*<<< orphan*/  t_state; } ;
struct TYPE_2__ {int /*<<< orphan*/  ref_task_tag; int /*<<< orphan*/  function; } ;

/* Variables and functions */
 int CMD_T_ABORTED ; 
 int CMD_T_ACTIVE ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRANSPORT_ISTATE_PROCESSING ; 
 int /*<<< orphan*/  pr_warn_ratelimited (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  target_handle_abort (struct se_cmd*) ; 
 int /*<<< orphan*/  target_tmr_work ; 

int transport_generic_handle_tmr(
	struct se_cmd *cmd)
{
	unsigned long flags;
	bool aborted = false;

	spin_lock_irqsave(&cmd->t_state_lock, flags);
	if (cmd->transport_state & CMD_T_ABORTED) {
		aborted = true;
	} else {
		cmd->t_state = TRANSPORT_ISTATE_PROCESSING;
		cmd->transport_state |= CMD_T_ACTIVE;
	}
	spin_unlock_irqrestore(&cmd->t_state_lock, flags);

	if (aborted) {
		pr_warn_ratelimited("handle_tmr caught CMD_T_ABORTED TMR %d ref_tag: %llu tag: %llu\n",
				    cmd->se_tmr_req->function,
				    cmd->se_tmr_req->ref_task_tag, cmd->tag);
		target_handle_abort(cmd);
		return 0;
	}

	INIT_WORK(&cmd->work, target_tmr_work);
	schedule_work(&cmd->work);
	return 0;
}