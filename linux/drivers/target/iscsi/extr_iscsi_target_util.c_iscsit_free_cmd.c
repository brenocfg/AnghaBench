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
struct se_cmd {scalar_t__ se_sess; scalar_t__ se_tfo; } ;
struct iscsi_cmd {int /*<<< orphan*/  i_conn_node; struct se_cmd se_cmd; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  __iscsit_free_cmd (struct iscsi_cmd*,int) ; 
 int /*<<< orphan*/  iscsit_release_cmd (struct iscsi_cmd*) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  target_put_sess_cmd (struct se_cmd*) ; 
 int transport_generic_free_cmd (struct se_cmd*,int) ; 

void iscsit_free_cmd(struct iscsi_cmd *cmd, bool shutdown)
{
	struct se_cmd *se_cmd = cmd->se_cmd.se_tfo ? &cmd->se_cmd : NULL;
	int rc;

	WARN_ON(!list_empty(&cmd->i_conn_node));

	__iscsit_free_cmd(cmd, shutdown);
	if (se_cmd) {
		rc = transport_generic_free_cmd(se_cmd, shutdown);
		if (!rc && shutdown && se_cmd->se_sess) {
			__iscsit_free_cmd(cmd, shutdown);
			target_put_sess_cmd(se_cmd);
		}
	} else {
		iscsit_release_cmd(cmd);
	}
}