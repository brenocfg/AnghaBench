#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct mlx5_wq_param {int /*<<< orphan*/  db_numa_node; int /*<<< orphan*/  buf_numa_node; } ;
struct mlx5_fpga_device {struct mlx5_core_dev* mdev; } ;
struct TYPE_3__ {int /*<<< orphan*/  wq_ctrl; int /*<<< orphan*/  wq; } ;
struct mlx5_fpga_conn {TYPE_1__ qp; struct mlx5_fpga_device* fdev; } ;
struct TYPE_4__ {int /*<<< orphan*/  numa_node; } ;
struct mlx5_core_dev {TYPE_2__ priv; } ;

/* Variables and functions */
 int mlx5_wq_qp_create (struct mlx5_core_dev*,struct mlx5_wq_param*,void*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int mlx5_fpga_conn_create_wq(struct mlx5_fpga_conn *conn, void *qpc)
{
	struct mlx5_fpga_device *fdev = conn->fdev;
	struct mlx5_core_dev *mdev = fdev->mdev;
	struct mlx5_wq_param wqp;

	wqp.buf_numa_node = mdev->priv.numa_node;
	wqp.db_numa_node  = mdev->priv.numa_node;

	return mlx5_wq_qp_create(mdev, &wqp, qpc, &conn->qp.wq,
				 &conn->qp.wq_ctrl);
}