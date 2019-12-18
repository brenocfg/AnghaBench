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
typedef  scalar_t__ u64 ;
struct mlx5_fpga_device {int /*<<< orphan*/  mdev; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOTCONN ; 
 size_t MLX5_FPGA_ACCESS_REG_SIZE_MAX ; 
 scalar_t__ min (size_t,size_t) ; 
 int mlx5_fpga_access_reg (int /*<<< orphan*/ ,scalar_t__,scalar_t__,scalar_t__*,int) ; 
 int /*<<< orphan*/  mlx5_fpga_err (struct mlx5_fpga_device*,char*,int) ; 

__attribute__((used)) static int mlx5_fpga_mem_read_i2c(struct mlx5_fpga_device *fdev, size_t size,
				  u64 addr, u8 *buf)
{
	size_t max_size = MLX5_FPGA_ACCESS_REG_SIZE_MAX;
	size_t bytes_done = 0;
	u8 actual_size;
	int err;

	if (!size)
		return -EINVAL;

	if (!fdev->mdev)
		return -ENOTCONN;

	while (bytes_done < size) {
		actual_size = min(max_size, (size - bytes_done));

		err = mlx5_fpga_access_reg(fdev->mdev, actual_size,
					   addr + bytes_done,
					   buf + bytes_done, false);
		if (err) {
			mlx5_fpga_err(fdev, "Failed to read over I2C: %d\n",
				      err);
			break;
		}

		bytes_done += actual_size;
	}

	return err;
}