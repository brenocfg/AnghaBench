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
struct mlx5_ib_dev {TYPE_2__* mdev; } ;
struct TYPE_3__ {int /*<<< orphan*/  uar; } ;
struct TYPE_4__ {TYPE_1__ priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  mlx5_put_uars_page (TYPE_2__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void mlx5_ib_stage_uar_cleanup(struct mlx5_ib_dev *dev)
{
	mlx5_put_uars_page(dev->mdev, dev->mdev->priv.uar);
}