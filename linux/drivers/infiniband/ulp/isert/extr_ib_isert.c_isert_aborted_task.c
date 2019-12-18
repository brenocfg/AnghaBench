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
struct isert_cmd {int dummy; } ;
struct iscsi_conn {int /*<<< orphan*/  cmd_lock; struct isert_conn* context; } ;
struct iscsi_cmd {scalar_t__ data_direction; int /*<<< orphan*/  i_conn_node; } ;

/* Variables and functions */
 scalar_t__ DMA_TO_DEVICE ; 
 struct isert_cmd* iscsit_priv_cmd (struct iscsi_cmd*) ; 
 int /*<<< orphan*/  iscsit_stop_dataout_timer (struct iscsi_cmd*) ; 
 int /*<<< orphan*/  isert_rdma_rw_ctx_destroy (struct isert_cmd*,struct isert_conn*) ; 
 int /*<<< orphan*/  list_del_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
isert_aborted_task(struct iscsi_conn *conn, struct iscsi_cmd *cmd)
{
	struct isert_cmd *isert_cmd = iscsit_priv_cmd(cmd);
	struct isert_conn *isert_conn = conn->context;

	spin_lock_bh(&conn->cmd_lock);
	if (!list_empty(&cmd->i_conn_node))
		list_del_init(&cmd->i_conn_node);
	spin_unlock_bh(&conn->cmd_lock);

	if (cmd->data_direction == DMA_TO_DEVICE)
		iscsit_stop_dataout_timer(cmd);
	isert_rdma_rw_ctx_destroy(isert_cmd, isert_conn);
}