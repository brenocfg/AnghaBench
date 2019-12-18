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
struct mlx5_fpga_device {int dummy; } ;
struct mlx5_core_dev {struct mlx5_fpga_device* fpga; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct mlx5_fpga_device*) ; 
 int /*<<< orphan*/  mlx5_fpga_device_stop (struct mlx5_core_dev*) ; 

void mlx5_fpga_cleanup(struct mlx5_core_dev *mdev)
{
	struct mlx5_fpga_device *fdev = mdev->fpga;

	mlx5_fpga_device_stop(mdev);
	kfree(fdev);
	mdev->fpga = NULL;
}