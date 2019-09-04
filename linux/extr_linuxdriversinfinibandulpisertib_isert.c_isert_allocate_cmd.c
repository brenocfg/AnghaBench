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
struct isert_conn {int dummy; } ;
struct isert_cmd {struct iser_rx_desc* rx_desc; struct iscsi_cmd* iscsi_cmd; struct isert_conn* conn; } ;
struct iser_rx_desc {int dummy; } ;
struct iscsi_conn {struct isert_conn* context; } ;
struct iscsi_cmd {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  TASK_INTERRUPTIBLE ; 
 struct iscsi_cmd* iscsit_allocate_cmd (struct iscsi_conn*,int /*<<< orphan*/ ) ; 
 struct isert_cmd* iscsit_priv_cmd (struct iscsi_cmd*) ; 
 int /*<<< orphan*/  isert_err (char*) ; 

__attribute__((used)) static struct iscsi_cmd
*isert_allocate_cmd(struct iscsi_conn *conn, struct iser_rx_desc *rx_desc)
{
	struct isert_conn *isert_conn = conn->context;
	struct isert_cmd *isert_cmd;
	struct iscsi_cmd *cmd;

	cmd = iscsit_allocate_cmd(conn, TASK_INTERRUPTIBLE);
	if (!cmd) {
		isert_err("Unable to allocate iscsi_cmd + isert_cmd\n");
		return NULL;
	}
	isert_cmd = iscsit_priv_cmd(cmd);
	isert_cmd->conn = isert_conn;
	isert_cmd->iscsi_cmd = cmd;
	isert_cmd->rx_desc = rx_desc;

	return cmd;
}