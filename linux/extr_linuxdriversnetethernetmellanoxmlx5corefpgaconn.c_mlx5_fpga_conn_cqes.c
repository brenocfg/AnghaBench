#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  cc; } ;
struct TYPE_5__ {TYPE_2__ wq; int /*<<< orphan*/  tasklet; } ;
struct mlx5_fpga_conn {TYPE_1__ cq; int /*<<< orphan*/  fdev; } ;
struct mlx5_cqe64 {int dummy; } ;

/* Variables and functions */
 struct mlx5_cqe64* mlx5_cqwq_get_cqe (TYPE_2__*) ; 
 int /*<<< orphan*/  mlx5_cqwq_pop (TYPE_2__*) ; 
 int /*<<< orphan*/  mlx5_cqwq_update_db_record (TYPE_2__*) ; 
 int /*<<< orphan*/  mlx5_fpga_conn_arm_cq (struct mlx5_fpga_conn*) ; 
 int /*<<< orphan*/  mlx5_fpga_conn_handle_cqe (struct mlx5_fpga_conn*,struct mlx5_cqe64*) ; 
 int /*<<< orphan*/  mlx5_fpga_dbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tasklet_schedule (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wmb () ; 

__attribute__((used)) static inline void mlx5_fpga_conn_cqes(struct mlx5_fpga_conn *conn,
				       unsigned int budget)
{
	struct mlx5_cqe64 *cqe;

	while (budget) {
		cqe = mlx5_cqwq_get_cqe(&conn->cq.wq);
		if (!cqe)
			break;

		budget--;
		mlx5_cqwq_pop(&conn->cq.wq);
		mlx5_fpga_conn_handle_cqe(conn, cqe);
		mlx5_cqwq_update_db_record(&conn->cq.wq);
	}
	if (!budget) {
		tasklet_schedule(&conn->cq.tasklet);
		return;
	}

	mlx5_fpga_dbg(conn->fdev, "Re-arming CQ with cc# %u\n", conn->cq.wq.cc);
	/* ensure cq space is freed before enabling more cqes */
	wmb();
	mlx5_fpga_conn_arm_cq(conn);
}