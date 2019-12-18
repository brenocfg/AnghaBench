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
struct se_cmd {int dummy; } ;
struct iscsi_session {int /*<<< orphan*/  se_sess; } ;
struct iscsi_cmd {int /*<<< orphan*/  text_in_ptr; int /*<<< orphan*/  iov_data; int /*<<< orphan*/  overflow_buf; int /*<<< orphan*/  tmr_req; int /*<<< orphan*/  seq_list; int /*<<< orphan*/  pdu_list; int /*<<< orphan*/  buf_ptr; struct iscsi_session* sess; TYPE_1__* conn; int /*<<< orphan*/  i_conn_node; struct se_cmd se_cmd; } ;
struct TYPE_2__ {struct iscsi_session* sess; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  target_free_tag (int /*<<< orphan*/ ,struct se_cmd*) ; 

void iscsit_release_cmd(struct iscsi_cmd *cmd)
{
	struct iscsi_session *sess;
	struct se_cmd *se_cmd = &cmd->se_cmd;

	WARN_ON(!list_empty(&cmd->i_conn_node));

	if (cmd->conn)
		sess = cmd->conn->sess;
	else
		sess = cmd->sess;

	BUG_ON(!sess || !sess->se_sess);

	kfree(cmd->buf_ptr);
	kfree(cmd->pdu_list);
	kfree(cmd->seq_list);
	kfree(cmd->tmr_req);
	kfree(cmd->overflow_buf);
	kfree(cmd->iov_data);
	kfree(cmd->text_in_ptr);

	target_free_tag(sess->se_sess, se_cmd);
}