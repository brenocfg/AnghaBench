#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  bufs; } ;
struct TYPE_6__ {int /*<<< orphan*/  bufs; } ;
struct TYPE_8__ {int /*<<< orphan*/  wq_ctrl; TYPE_3__ rq; TYPE_2__ sq; int /*<<< orphan*/  mqp; } ;
struct mlx5_fpga_conn {TYPE_4__ qp; TYPE_1__* fdev; } ;
struct TYPE_5__ {int /*<<< orphan*/  mdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  kvfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlx5_core_destroy_qp (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mlx5_fpga_conn_flush_send_bufs (struct mlx5_fpga_conn*) ; 
 int /*<<< orphan*/  mlx5_fpga_conn_free_recv_bufs (struct mlx5_fpga_conn*) ; 
 int /*<<< orphan*/  mlx5_wq_destroy (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void mlx5_fpga_conn_destroy_qp(struct mlx5_fpga_conn *conn)
{
	mlx5_core_destroy_qp(conn->fdev->mdev, &conn->qp.mqp);
	mlx5_fpga_conn_free_recv_bufs(conn);
	mlx5_fpga_conn_flush_send_bufs(conn);
	kvfree(conn->qp.sq.bufs);
	kvfree(conn->qp.rq.bufs);
	mlx5_wq_destroy(&conn->qp.wq_ctrl);
}