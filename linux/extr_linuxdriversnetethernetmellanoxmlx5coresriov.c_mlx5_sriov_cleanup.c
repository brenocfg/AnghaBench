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
struct mlx5_core_sriov {int /*<<< orphan*/  vfs_ctx; } ;
struct TYPE_2__ {struct mlx5_core_sriov sriov; } ;
struct mlx5_core_dev {TYPE_1__ priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlx5_core_is_pf (struct mlx5_core_dev*) ; 

void mlx5_sriov_cleanup(struct mlx5_core_dev *dev)
{
	struct mlx5_core_sriov *sriov = &dev->priv.sriov;

	if (!mlx5_core_is_pf(dev))
		return;

	kfree(sriov->vfs_ctx);
}