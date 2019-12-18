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
typedef  int /*<<< orphan*/  u8 ;
struct iscsi_conn {int /*<<< orphan*/  cmd_lock; int /*<<< orphan*/  conn_cmd_list; int /*<<< orphan*/  sess; } ;
struct iscsi_cmd {int targ_xfer_tag; int /*<<< orphan*/  i_conn_node; int /*<<< orphan*/  init_task_tag; int /*<<< orphan*/  iscsi_opcode; } ;

/* Variables and functions */
 int /*<<< orphan*/  ISCSI_OP_NOOP_IN ; 
 int /*<<< orphan*/  ISTATE_SEND_NOPIN_NO_RESPONSE ; 
 int /*<<< orphan*/  ISTATE_SEND_NOPIN_WANT_RESPONSE ; 
 int /*<<< orphan*/  RESERVED_ITT ; 
 int /*<<< orphan*/  TASK_RUNNING ; 
 int /*<<< orphan*/  iscsit_add_cmd_to_immediate_queue (struct iscsi_cmd*,struct iscsi_conn*,int /*<<< orphan*/ ) ; 
 struct iscsi_cmd* iscsit_allocate_cmd (struct iscsi_conn*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iscsit_start_nopin_response_timer (struct iscsi_conn*) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int session_get_next_ttt (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int iscsit_add_nopin(struct iscsi_conn *conn, int want_response)
{
	u8 state;
	struct iscsi_cmd *cmd;

	cmd = iscsit_allocate_cmd(conn, TASK_RUNNING);
	if (!cmd)
		return -1;

	cmd->iscsi_opcode = ISCSI_OP_NOOP_IN;
	state = (want_response) ? ISTATE_SEND_NOPIN_WANT_RESPONSE :
				ISTATE_SEND_NOPIN_NO_RESPONSE;
	cmd->init_task_tag = RESERVED_ITT;
	cmd->targ_xfer_tag = (want_response) ?
			     session_get_next_ttt(conn->sess) : 0xFFFFFFFF;
	spin_lock_bh(&conn->cmd_lock);
	list_add_tail(&cmd->i_conn_node, &conn->conn_cmd_list);
	spin_unlock_bh(&conn->cmd_lock);

	if (want_response)
		iscsit_start_nopin_response_timer(conn);
	iscsit_add_cmd_to_immediate_queue(cmd, conn, state);

	return 0;
}