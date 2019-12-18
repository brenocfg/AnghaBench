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
struct TYPE_2__ {int /*<<< orphan*/  dbg_root; } ;
struct mlx5_core_dev {TYPE_1__ priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  debugfs_remove_recursive (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlx5_health_cleanup (struct mlx5_core_dev*) ; 
 int /*<<< orphan*/  mlx5_pagealloc_cleanup (struct mlx5_core_dev*) ; 

__attribute__((used)) static void mlx5_mdev_uninit(struct mlx5_core_dev *dev)
{
	mlx5_pagealloc_cleanup(dev);
	mlx5_health_cleanup(dev);
	debugfs_remove_recursive(dev->priv.dbg_root);
}