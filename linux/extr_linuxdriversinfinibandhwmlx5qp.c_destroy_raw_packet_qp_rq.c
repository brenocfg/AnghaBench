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
struct TYPE_2__ {int /*<<< orphan*/  mqp; } ;
struct mlx5_ib_rq {TYPE_1__ base; } ;
struct mlx5_ib_dev {int /*<<< orphan*/  mdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  mlx5_core_destroy_rq_tracked (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void destroy_raw_packet_qp_rq(struct mlx5_ib_dev *dev,
				     struct mlx5_ib_rq *rq)
{
	mlx5_core_destroy_rq_tracked(dev->mdev, &rq->base.mqp);
}