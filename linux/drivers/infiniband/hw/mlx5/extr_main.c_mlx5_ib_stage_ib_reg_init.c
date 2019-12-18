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
struct mlx5_ib_dev {int /*<<< orphan*/  ib_dev; int /*<<< orphan*/  mdev; } ;

/* Variables and functions */
 int ib_register_device (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  mlx5_attr_group ; 
 int /*<<< orphan*/  mlx5_lag_is_roce (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rdma_set_device_sysfs_group (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int mlx5_ib_stage_ib_reg_init(struct mlx5_ib_dev *dev)
{
	const char *name;

	rdma_set_device_sysfs_group(&dev->ib_dev, &mlx5_attr_group);
	if (!mlx5_lag_is_roce(dev->mdev))
		name = "mlx5_%d";
	else
		name = "mlx5_bond_%d";
	return ib_register_device(&dev->ib_dev, name);
}