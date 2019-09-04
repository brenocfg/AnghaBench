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
struct isert_cmd {int dummy; } ;
struct iscsi_conn {int /*<<< orphan*/  cmd_lock; } ;
struct iscsi_cmd {int /*<<< orphan*/  i_conn_node; } ;

/* Variables and functions */
 int EINVAL ; 
#define  ISTATE_REMOVE 129 
#define  ISTATE_SEND_NOPIN_WANT_RESPONSE 128 
 struct isert_cmd* iscsit_priv_cmd (struct iscsi_cmd*) ; 
 int /*<<< orphan*/  isert_err (char*,int) ; 
 int /*<<< orphan*/  isert_put_cmd (struct isert_cmd*,int) ; 
 int isert_put_nopin (struct iscsi_cmd*,struct iscsi_conn*,int) ; 
 int /*<<< orphan*/  list_del_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
isert_immediate_queue(struct iscsi_conn *conn, struct iscsi_cmd *cmd, int state)
{
	struct isert_cmd *isert_cmd = iscsit_priv_cmd(cmd);
	int ret = 0;

	switch (state) {
	case ISTATE_REMOVE:
		spin_lock_bh(&conn->cmd_lock);
		list_del_init(&cmd->i_conn_node);
		spin_unlock_bh(&conn->cmd_lock);
		isert_put_cmd(isert_cmd, true);
		break;
	case ISTATE_SEND_NOPIN_WANT_RESPONSE:
		ret = isert_put_nopin(cmd, conn, false);
		break;
	default:
		isert_err("Unknown immediate state: 0x%02x\n", state);
		ret = -EINVAL;
		break;
	}

	return ret;
}