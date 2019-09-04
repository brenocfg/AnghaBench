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
struct TYPE_2__ {int /*<<< orphan*/  complete; } ;
struct mlx5_fpga_tls_command_context {int /*<<< orphan*/  list; TYPE_1__ buf; int /*<<< orphan*/  (* complete ) (int /*<<< orphan*/ ,struct mlx5_fpga_device*,struct mlx5_fpga_tls_command_context*,int /*<<< orphan*/ *) ;int /*<<< orphan*/  ref; } ;
struct mlx5_fpga_tls {int /*<<< orphan*/  pending_cmds_lock; int /*<<< orphan*/  conn; int /*<<< orphan*/  pending_cmds; } ;
struct mlx5_fpga_device {struct mlx5_fpga_tls* tls; } ;
typedef  int /*<<< orphan*/  (* mlx5_fpga_tls_command_complete ) (int /*<<< orphan*/ ,struct mlx5_fpga_device*,struct mlx5_fpga_tls_command_context*,int /*<<< orphan*/ *) ;

/* Variables and functions */
 scalar_t__ likely (int) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mlx5_fpga_cmd_send_complete ; 
 int mlx5_fpga_sbu_conn_sendmsg (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  refcount_set (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void mlx5_fpga_tls_cmd_send(struct mlx5_fpga_device *fdev,
				   struct mlx5_fpga_tls_command_context *cmd,
				   mlx5_fpga_tls_command_complete complete)
{
	struct mlx5_fpga_tls *tls = fdev->tls;
	unsigned long flags;
	int ret;

	refcount_set(&cmd->ref, 2);
	cmd->complete = complete;
	cmd->buf.complete = mlx5_fpga_cmd_send_complete;

	spin_lock_irqsave(&tls->pending_cmds_lock, flags);
	/* mlx5_fpga_sbu_conn_sendmsg is called under pending_cmds_lock
	 * to make sure commands are inserted to the tls->pending_cmds list
	 * and the command QP in the same order.
	 */
	ret = mlx5_fpga_sbu_conn_sendmsg(tls->conn, &cmd->buf);
	if (likely(!ret))
		list_add_tail(&cmd->list, &tls->pending_cmds);
	else
		complete(tls->conn, fdev, cmd, NULL);
	spin_unlock_irqrestore(&tls->pending_cmds_lock, flags);
}