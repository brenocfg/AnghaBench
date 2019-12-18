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
struct iscsi_conn {int /*<<< orphan*/  cmd_lock; } ;
struct TYPE_2__ {int transport_state; } ;
struct iscsi_cmd {int /*<<< orphan*/  i_conn_node; TYPE_1__ se_cmd; } ;

/* Variables and functions */
 int CMD_T_FABRIC_STOP ; 
 int /*<<< orphan*/  __iscsit_free_cmd (struct iscsi_cmd*,int) ; 
 int /*<<< orphan*/  list_del_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

void iscsit_aborted_task(struct iscsi_conn *conn, struct iscsi_cmd *cmd)
{
	spin_lock_bh(&conn->cmd_lock);
	if (!list_empty(&cmd->i_conn_node) &&
	    !(cmd->se_cmd.transport_state & CMD_T_FABRIC_STOP))
		list_del_init(&cmd->i_conn_node);
	spin_unlock_bh(&conn->cmd_lock);

	__iscsit_free_cmd(cmd, true);
}