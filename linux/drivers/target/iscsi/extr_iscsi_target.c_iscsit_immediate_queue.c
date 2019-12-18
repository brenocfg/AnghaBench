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
struct iscsi_conn {int /*<<< orphan*/  cid; int /*<<< orphan*/  cmd_lock; } ;
struct iscsi_cmd {int /*<<< orphan*/  init_task_tag; int /*<<< orphan*/  iscsi_opcode; int /*<<< orphan*/  i_conn_node; } ;

/* Variables and functions */
#define  ISTATE_REMOVE 131 
#define  ISTATE_SEND_NOPIN_NO_RESPONSE 130 
#define  ISTATE_SEND_NOPIN_WANT_RESPONSE 129 
#define  ISTATE_SEND_R2T 128 
 int /*<<< orphan*/  iscsit_free_cmd (struct iscsi_cmd*,int) ; 
 int /*<<< orphan*/  iscsit_mod_nopin_response_timer (struct iscsi_conn*) ; 
 int iscsit_send_r2t (struct iscsi_cmd*,struct iscsi_conn*) ; 
 int iscsit_send_unsolicited_nopin (struct iscsi_cmd*,struct iscsi_conn*,int) ; 
 int /*<<< orphan*/  list_del_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_err (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

int
iscsit_immediate_queue(struct iscsi_conn *conn, struct iscsi_cmd *cmd, int state)
{
	int ret;

	switch (state) {
	case ISTATE_SEND_R2T:
		ret = iscsit_send_r2t(cmd, conn);
		if (ret < 0)
			goto err;
		break;
	case ISTATE_REMOVE:
		spin_lock_bh(&conn->cmd_lock);
		list_del_init(&cmd->i_conn_node);
		spin_unlock_bh(&conn->cmd_lock);

		iscsit_free_cmd(cmd, false);
		break;
	case ISTATE_SEND_NOPIN_WANT_RESPONSE:
		iscsit_mod_nopin_response_timer(conn);
		ret = iscsit_send_unsolicited_nopin(cmd, conn, 1);
		if (ret < 0)
			goto err;
		break;
	case ISTATE_SEND_NOPIN_NO_RESPONSE:
		ret = iscsit_send_unsolicited_nopin(cmd, conn, 0);
		if (ret < 0)
			goto err;
		break;
	default:
		pr_err("Unknown Opcode: 0x%02x ITT:"
		       " 0x%08x, i_state: %d on CID: %hu\n",
		       cmd->iscsi_opcode, cmd->init_task_tag, state,
		       conn->cid);
		goto err;
	}

	return 0;

err:
	return -1;
}