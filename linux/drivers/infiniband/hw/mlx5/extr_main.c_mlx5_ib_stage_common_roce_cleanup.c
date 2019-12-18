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
typedef  scalar_t__ u8 ;
struct mlx5_ib_dev {int /*<<< orphan*/  mdev; } ;

/* Variables and functions */
 scalar_t__ mlx5_core_native_port_num (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlx5_remove_netdev_notifier (struct mlx5_ib_dev*,scalar_t__) ; 

__attribute__((used)) static void mlx5_ib_stage_common_roce_cleanup(struct mlx5_ib_dev *dev)
{
	u8 port_num = mlx5_core_native_port_num(dev->mdev) - 1;

	mlx5_remove_netdev_notifier(dev, port_num);
}