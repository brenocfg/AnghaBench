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
struct iscsi_conn {TYPE_1__* conn_transport; } ;
struct iscsi_cmd {scalar_t__ data_direction; int /*<<< orphan*/  i_conn_node; struct iscsi_conn* conn; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* iscsit_unmap_cmd ) (struct iscsi_conn*,struct iscsi_cmd*) ;} ;

/* Variables and functions */
 scalar_t__ DMA_FROM_DEVICE ; 
 scalar_t__ DMA_TO_DEVICE ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  iscsit_free_all_datain_reqs (struct iscsi_cmd*) ; 
 int /*<<< orphan*/  iscsit_free_r2ts_from_list (struct iscsi_cmd*) ; 
 int /*<<< orphan*/  iscsit_remove_cmd_from_immediate_queue (struct iscsi_cmd*,struct iscsi_conn*) ; 
 int /*<<< orphan*/  iscsit_remove_cmd_from_response_queue (struct iscsi_cmd*,struct iscsi_conn*) ; 
 int /*<<< orphan*/  iscsit_stop_dataout_timer (struct iscsi_cmd*) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct iscsi_conn*,struct iscsi_cmd*) ; 

void __iscsit_free_cmd(struct iscsi_cmd *cmd, bool check_queues)
{
	struct iscsi_conn *conn = cmd->conn;

	WARN_ON(!list_empty(&cmd->i_conn_node));

	if (cmd->data_direction == DMA_TO_DEVICE) {
		iscsit_stop_dataout_timer(cmd);
		iscsit_free_r2ts_from_list(cmd);
	}
	if (cmd->data_direction == DMA_FROM_DEVICE)
		iscsit_free_all_datain_reqs(cmd);

	if (conn && check_queues) {
		iscsit_remove_cmd_from_immediate_queue(cmd, conn);
		iscsit_remove_cmd_from_response_queue(cmd, conn);
	}

	if (conn && conn->conn_transport->iscsit_unmap_cmd)
		conn->conn_transport->iscsit_unmap_cmd(conn, cmd);
}