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
struct mlx5_core_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  mlx5_core_is_pf (struct mlx5_core_dev*) ; 
 int /*<<< orphan*/  mlx5_device_disable_sriov (struct mlx5_core_dev*) ; 

void mlx5_sriov_detach(struct mlx5_core_dev *dev)
{
	if (!mlx5_core_is_pf(dev))
		return;

	mlx5_device_disable_sriov(dev);
}