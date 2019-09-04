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
typedef  int /*<<< orphan*/  u64 ;
struct mlx5_fpga_device {int dummy; } ;
typedef  enum mlx5_fpga_access_type { ____Placeholder_mlx5_fpga_access_type } mlx5_fpga_access_type ;

/* Variables and functions */
 int EACCES ; 
#define  MLX5_FPGA_ACCESS_TYPE_I2C 128 
 int mlx5_fpga_mem_read_i2c (struct mlx5_fpga_device*,size_t,int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  mlx5_fpga_warn (struct mlx5_fpga_device*,char*,int) ; 

int mlx5_fpga_mem_read(struct mlx5_fpga_device *fdev, size_t size, u64 addr,
		       void *buf, enum mlx5_fpga_access_type access_type)
{
	int ret;

	switch (access_type) {
	case MLX5_FPGA_ACCESS_TYPE_I2C:
		ret = mlx5_fpga_mem_read_i2c(fdev, size, addr, buf);
		if (ret)
			return ret;
		break;
	default:
		mlx5_fpga_warn(fdev, "Unexpected read access_type %u\n",
			       access_type);
		return -EACCES;
	}

	return size;
}