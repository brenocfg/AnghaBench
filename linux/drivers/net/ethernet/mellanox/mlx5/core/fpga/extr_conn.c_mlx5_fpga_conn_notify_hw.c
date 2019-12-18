#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_7__ ;
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/  pc; } ;
struct TYPE_8__ {int /*<<< orphan*/ * db; } ;
struct TYPE_9__ {TYPE_1__ sq; } ;
struct TYPE_11__ {TYPE_3__ sq; TYPE_2__ wq; } ;
struct mlx5_fpga_conn {TYPE_7__* fdev; TYPE_4__ qp; } ;
struct TYPE_13__ {TYPE_5__* uar; } ;
struct TYPE_14__ {TYPE_6__ conn_res; } ;
struct TYPE_12__ {scalar_t__ map; } ;

/* Variables and functions */
 scalar_t__ MLX5_BF_OFFSET ; 
 int /*<<< orphan*/  cpu_to_be32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_wmb () ; 
 int /*<<< orphan*/  mlx5_write64 (void*,scalar_t__) ; 
 int /*<<< orphan*/  wmb () ; 

__attribute__((used)) static void mlx5_fpga_conn_notify_hw(struct mlx5_fpga_conn *conn, void *wqe)
{
	/* ensure wqe is visible to device before updating doorbell record */
	dma_wmb();
	*conn->qp.wq.sq.db = cpu_to_be32(conn->qp.sq.pc);
	/* Make sure that doorbell record is visible before ringing */
	wmb();
	mlx5_write64(wqe, conn->fdev->conn_res.uar->map + MLX5_BF_OFFSET);
}