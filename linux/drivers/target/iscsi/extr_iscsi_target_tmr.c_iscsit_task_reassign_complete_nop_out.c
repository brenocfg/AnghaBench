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
struct iscsi_tmr_req {struct iscsi_cmd* ref_cmd; } ;
struct iscsi_conn_recovery {int dummy; } ;
struct iscsi_conn {int /*<<< orphan*/  cmd_lock; int /*<<< orphan*/  conn_cmd_list; int /*<<< orphan*/  sess; } ;
struct iscsi_cmd {int /*<<< orphan*/  i_state; int /*<<< orphan*/  i_conn_node; scalar_t__ exp_stat_sn; scalar_t__ stat_sn; struct iscsi_conn_recovery* cr; int /*<<< orphan*/  init_task_tag; } ;

/* Variables and functions */
 int /*<<< orphan*/  ISTATE_SEND_NOPIN ; 
 int /*<<< orphan*/  iscsit_add_cmd_to_response_queue (struct iscsi_cmd*,struct iscsi_conn*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iscsit_task_reassign_remove_cmd (struct iscsi_cmd*,struct iscsi_conn_recovery*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_err (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int iscsit_task_reassign_complete_nop_out(
	struct iscsi_tmr_req *tmr_req,
	struct iscsi_conn *conn)
{
	struct iscsi_cmd *cmd = tmr_req->ref_cmd;
	struct iscsi_conn_recovery *cr;

	if (!cmd->cr) {
		pr_err("struct iscsi_conn_recovery pointer for ITT: 0x%08x"
			" is NULL!\n", cmd->init_task_tag);
		return -1;
	}
	cr = cmd->cr;

	/*
	 * Reset the StatSN so a new one for this commands new connection
	 * will be assigned.
	 * Reset the ExpStatSN as well so we may receive Status SNACKs.
	 */
	cmd->stat_sn = cmd->exp_stat_sn = 0;

	iscsit_task_reassign_remove_cmd(cmd, cr, conn->sess);

	spin_lock_bh(&conn->cmd_lock);
	list_add_tail(&cmd->i_conn_node, &conn->conn_cmd_list);
	spin_unlock_bh(&conn->cmd_lock);

	cmd->i_state = ISTATE_SEND_NOPIN;
	iscsit_add_cmd_to_response_queue(cmd, conn, cmd->i_state);
	return 0;
}