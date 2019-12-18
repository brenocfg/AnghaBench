#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  cc; } ;
struct TYPE_10__ {TYPE_4__ wq; int /*<<< orphan*/  mcq; } ;
struct mlx5_fpga_conn {TYPE_5__ cq; TYPE_3__* fdev; } ;
struct TYPE_7__ {TYPE_1__* uar; } ;
struct TYPE_8__ {TYPE_2__ conn_res; } ;
struct TYPE_6__ {int /*<<< orphan*/  map; } ;

/* Variables and functions */
 int /*<<< orphan*/  MLX5_CQ_DB_REQ_NOT ; 
 int /*<<< orphan*/  mlx5_cq_arm (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void mlx5_fpga_conn_arm_cq(struct mlx5_fpga_conn *conn)
{
	mlx5_cq_arm(&conn->cq.mcq, MLX5_CQ_DB_REQ_NOT,
		    conn->fdev->conn_res.uar->map, conn->cq.wq.cc);
}