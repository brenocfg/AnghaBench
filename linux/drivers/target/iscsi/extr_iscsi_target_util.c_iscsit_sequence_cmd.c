#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct iscsi_conn {TYPE_1__* sess; } ;
struct iscsi_cmd {int /*<<< orphan*/  i_state; } ;
typedef  int /*<<< orphan*/  __be32 ;
struct TYPE_4__ {int /*<<< orphan*/  cmdsn_mutex; int /*<<< orphan*/  sess_ooo_cmdsn_list; } ;

/* Variables and functions */
 int CMDSN_ERROR_CANNOT_RECOVER ; 
#define  CMDSN_HIGHER_THAN_EXP 131 
#define  CMDSN_LOWER_THAN_EXP 130 
#define  CMDSN_MAXCMDSN_OVERRUN 129 
#define  CMDSN_NORMAL_OPERATION 128 
 int /*<<< orphan*/  ISCSI_REASON_BOOKMARK_NO_RESOURCES ; 
 int /*<<< orphan*/  ISTATE_REMOVE ; 
 int /*<<< orphan*/  be32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iscsit_add_cmd_to_immediate_queue (struct iscsi_cmd*,struct iscsi_conn*,int /*<<< orphan*/ ) ; 
 int iscsit_check_received_cmdsn (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int iscsit_execute_cmd (struct iscsi_cmd*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iscsit_execute_ooo_cmdsns (TYPE_1__*) ; 
 int iscsit_handle_ooo_cmdsn (TYPE_1__*,struct iscsi_cmd*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iscsit_reject_cmd (struct iscsi_cmd*,int /*<<< orphan*/ ,unsigned char*) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

int iscsit_sequence_cmd(struct iscsi_conn *conn, struct iscsi_cmd *cmd,
			unsigned char *buf, __be32 cmdsn)
{
	int ret, cmdsn_ret;
	bool reject = false;
	u8 reason = ISCSI_REASON_BOOKMARK_NO_RESOURCES;

	mutex_lock(&conn->sess->cmdsn_mutex);

	cmdsn_ret = iscsit_check_received_cmdsn(conn->sess, be32_to_cpu(cmdsn));
	switch (cmdsn_ret) {
	case CMDSN_NORMAL_OPERATION:
		ret = iscsit_execute_cmd(cmd, 0);
		if ((ret >= 0) && !list_empty(&conn->sess->sess_ooo_cmdsn_list))
			iscsit_execute_ooo_cmdsns(conn->sess);
		else if (ret < 0) {
			reject = true;
			ret = CMDSN_ERROR_CANNOT_RECOVER;
		}
		break;
	case CMDSN_HIGHER_THAN_EXP:
		ret = iscsit_handle_ooo_cmdsn(conn->sess, cmd, be32_to_cpu(cmdsn));
		if (ret < 0) {
			reject = true;
			ret = CMDSN_ERROR_CANNOT_RECOVER;
			break;
		}
		ret = CMDSN_HIGHER_THAN_EXP;
		break;
	case CMDSN_LOWER_THAN_EXP:
	case CMDSN_MAXCMDSN_OVERRUN:
	default:
		cmd->i_state = ISTATE_REMOVE;
		iscsit_add_cmd_to_immediate_queue(cmd, conn, cmd->i_state);
		/*
		 * Existing callers for iscsit_sequence_cmd() will silently
		 * ignore commands with CMDSN_LOWER_THAN_EXP, so force this
		 * return for CMDSN_MAXCMDSN_OVERRUN as well..
		 */
		ret = CMDSN_LOWER_THAN_EXP;
		break;
	}
	mutex_unlock(&conn->sess->cmdsn_mutex);

	if (reject)
		iscsit_reject_cmd(cmd, reason, buf);

	return ret;
}