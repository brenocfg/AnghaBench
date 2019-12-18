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
struct se_cmd {int transport_state; int /*<<< orphan*/  t_transport_stop_comp; int /*<<< orphan*/  (* transport_complete_callback ) (struct se_cmd*,int,int*) ;int /*<<< orphan*/  work; } ;

/* Variables and functions */
 int CMD_T_ABORTED ; 
 int CMD_T_STOP ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  complete_all (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct se_cmd*,int,int*) ; 
 int /*<<< orphan*/  stub2 (struct se_cmd*,int,int*) ; 
 int /*<<< orphan*/  target_abort_work ; 
 int /*<<< orphan*/  target_completion_wq ; 

__attribute__((used)) static bool target_cmd_interrupted(struct se_cmd *cmd)
{
	int post_ret;

	if (cmd->transport_state & CMD_T_ABORTED) {
		if (cmd->transport_complete_callback)
			cmd->transport_complete_callback(cmd, false, &post_ret);
		INIT_WORK(&cmd->work, target_abort_work);
		queue_work(target_completion_wq, &cmd->work);
		return true;
	} else if (cmd->transport_state & CMD_T_STOP) {
		if (cmd->transport_complete_callback)
			cmd->transport_complete_callback(cmd, false, &post_ret);
		complete_all(&cmd->t_transport_stop_comp);
		return true;
	}

	return false;
}