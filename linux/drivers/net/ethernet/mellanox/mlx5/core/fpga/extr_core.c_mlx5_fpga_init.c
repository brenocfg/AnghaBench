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
struct mlx5_fpga_device {struct mlx5_core_dev* mdev; } ;
struct mlx5_core_dev {struct mlx5_fpga_device* fpga; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  MLX5_CAP_GEN (struct mlx5_core_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fpga ; 
 int /*<<< orphan*/  mlx5_core_dbg (struct mlx5_core_dev*,char*) ; 
 struct mlx5_fpga_device* mlx5_fpga_device_alloc () ; 

int mlx5_fpga_init(struct mlx5_core_dev *mdev)
{
	struct mlx5_fpga_device *fdev = NULL;

	if (!MLX5_CAP_GEN(mdev, fpga)) {
		mlx5_core_dbg(mdev, "FPGA capability not present\n");
		return 0;
	}

	mlx5_core_dbg(mdev, "Initializing FPGA\n");

	fdev = mlx5_fpga_device_alloc();
	if (!fdev)
		return -ENOMEM;

	fdev->mdev = mdev;
	mdev->fpga = fdev;

	return 0;
}