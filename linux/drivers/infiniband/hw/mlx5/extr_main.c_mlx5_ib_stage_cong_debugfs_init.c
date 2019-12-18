#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct mlx5_ib_dev {int /*<<< orphan*/  mdev; } ;

/* Variables and functions */
 scalar_t__ mlx5_core_native_port_num (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlx5_ib_init_cong_debugfs (struct mlx5_ib_dev*,scalar_t__) ; 

__attribute__((used)) static int mlx5_ib_stage_cong_debugfs_init(struct mlx5_ib_dev *dev)
{
	mlx5_ib_init_cong_debugfs(dev,
				  mlx5_core_native_port_num(dev->mdev) - 1);
	return 0;
}