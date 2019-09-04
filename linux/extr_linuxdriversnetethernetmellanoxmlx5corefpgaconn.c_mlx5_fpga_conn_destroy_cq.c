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
struct TYPE_4__ {int /*<<< orphan*/  wq_ctrl; int /*<<< orphan*/  mcq; int /*<<< orphan*/  tasklet; } ;
struct mlx5_fpga_conn {TYPE_2__ cq; TYPE_1__* fdev; } ;
struct TYPE_3__ {int /*<<< orphan*/  mdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  mlx5_core_destroy_cq (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mlx5_wq_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tasklet_disable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tasklet_kill (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void mlx5_fpga_conn_destroy_cq(struct mlx5_fpga_conn *conn)
{
	tasklet_disable(&conn->cq.tasklet);
	tasklet_kill(&conn->cq.tasklet);
	mlx5_core_destroy_cq(conn->fdev->mdev, &conn->cq.mcq);
	mlx5_wq_destroy(&conn->cq.wq_ctrl);
}