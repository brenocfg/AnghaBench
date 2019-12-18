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
struct TYPE_4__ {int /*<<< orphan*/  umem; } ;
struct TYPE_3__ {int /*<<< orphan*/  mqp; } ;
struct mlx5_ib_sq {TYPE_2__ ubuffer; TYPE_1__ base; } ;
struct mlx5_ib_dev {int /*<<< orphan*/  mdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  destroy_flow_rule_vport_sq (struct mlx5_ib_sq*) ; 
 int /*<<< orphan*/  ib_umem_release (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlx5_core_destroy_sq_tracked (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void destroy_raw_packet_qp_sq(struct mlx5_ib_dev *dev,
				     struct mlx5_ib_sq *sq)
{
	destroy_flow_rule_vport_sq(sq);
	mlx5_core_destroy_sq_tracked(dev->mdev, &sq->base.mqp);
	ib_umem_release(sq->ubuffer.umem);
}