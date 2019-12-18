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
struct TYPE_7__ {int pc; } ;
struct TYPE_5__ {int /*<<< orphan*/ * db; } ;
struct TYPE_6__ {TYPE_1__ sq; } ;
struct mlx5dr_qp {TYPE_4__* uar; TYPE_3__ sq; TYPE_2__ wq; } ;
struct TYPE_8__ {scalar_t__ map; } ;

/* Variables and functions */
 scalar_t__ MLX5_BF_OFFSET ; 
 int /*<<< orphan*/  cpu_to_be32 (int) ; 
 int /*<<< orphan*/  dma_wmb () ; 
 int /*<<< orphan*/  mlx5_write64 (void*,scalar_t__) ; 
 int /*<<< orphan*/  wmb () ; 

__attribute__((used)) static void dr_cmd_notify_hw(struct mlx5dr_qp *dr_qp, void *ctrl)
{
	dma_wmb();
	*dr_qp->wq.sq.db = cpu_to_be32(dr_qp->sq.pc & 0xfffff);

	/* After wmb() the hw aware of new work */
	wmb();

	mlx5_write64(ctrl, dr_qp->uar->map + MLX5_BF_OFFSET);
}