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
typedef  int /*<<< orphan*/  u8 ;
struct iscsi_conn {int /*<<< orphan*/  cmd_lock; int /*<<< orphan*/  conn_cmd_list; } ;
struct TYPE_2__ {int /*<<< orphan*/ * se_tfo; } ;
struct iscsi_cmd {TYPE_1__ se_cmd; int /*<<< orphan*/  i_state; int /*<<< orphan*/  i_conn_node; int /*<<< orphan*/  buf_ptr; int /*<<< orphan*/  reject_reason; int /*<<< orphan*/  iscsi_opcode; struct iscsi_conn* conn; int /*<<< orphan*/  init_task_tag; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  ISCSI_HDR_LEN ; 
 int /*<<< orphan*/  ISCSI_OP_REJECT ; 
 int /*<<< orphan*/  ISTATE_SEND_REJECT ; 
 int /*<<< orphan*/  iscsit_add_cmd_to_response_queue (struct iscsi_cmd*,struct iscsi_conn*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iscsit_free_cmd (struct iscsi_cmd*,int) ; 
 int /*<<< orphan*/  kmemdup (unsigned char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_debug (char*) ; 
 int /*<<< orphan*/  pr_err (char*,...) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  target_put_sess_cmd (TYPE_1__*) ; 

__attribute__((used)) static int iscsit_add_reject_from_cmd(
	struct iscsi_cmd *cmd,
	u8 reason,
	bool add_to_conn,
	unsigned char *buf)
{
	struct iscsi_conn *conn;
	const bool do_put = cmd->se_cmd.se_tfo != NULL;

	if (!cmd->conn) {
		pr_err("cmd->conn is NULL for ITT: 0x%08x\n",
				cmd->init_task_tag);
		return -1;
	}
	conn = cmd->conn;

	cmd->iscsi_opcode = ISCSI_OP_REJECT;
	cmd->reject_reason = reason;

	cmd->buf_ptr = kmemdup(buf, ISCSI_HDR_LEN, GFP_KERNEL);
	if (!cmd->buf_ptr) {
		pr_err("Unable to allocate memory for cmd->buf_ptr\n");
		iscsit_free_cmd(cmd, false);
		return -1;
	}

	if (add_to_conn) {
		spin_lock_bh(&conn->cmd_lock);
		list_add_tail(&cmd->i_conn_node, &conn->conn_cmd_list);
		spin_unlock_bh(&conn->cmd_lock);
	}

	cmd->i_state = ISTATE_SEND_REJECT;
	iscsit_add_cmd_to_response_queue(cmd, conn, cmd->i_state);
	/*
	 * Perform the kref_put now if se_cmd has already been setup by
	 * scsit_setup_scsi_cmd()
	 */
	if (do_put) {
		pr_debug("iscsi reject: calling target_put_sess_cmd >>>>>>\n");
		target_put_sess_cmd(&cmd->se_cmd);
	}
	return -1;
}