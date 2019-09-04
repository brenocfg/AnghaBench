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
struct TYPE_2__ {int /*<<< orphan*/  active; } ;
struct mlx5_fpga_conn {TYPE_1__ qp; } ;

/* Variables and functions */
 int /*<<< orphan*/  MLX5_FPGA_CQ_BUDGET ; 
 int /*<<< orphan*/  mlx5_fpga_conn_cqes (struct mlx5_fpga_conn*,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static void mlx5_fpga_conn_cq_tasklet(unsigned long data)
{
	struct mlx5_fpga_conn *conn = (void *)data;

	if (unlikely(!conn->qp.active))
		return;
	mlx5_fpga_conn_cqes(conn, MLX5_FPGA_CQ_BUDGET);
}