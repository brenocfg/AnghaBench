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
typedef  enum mlx5_fpga_image { ____Placeholder_mlx5_fpga_image } mlx5_fpga_image ;

/* Variables and functions */
#define  MLX5_FPGA_IMAGE_FACTORY 129 
#define  MLX5_FPGA_IMAGE_USER 128 

__attribute__((used)) static const char *mlx5_fpga_image_name(enum mlx5_fpga_image image)
{
	switch (image) {
	case MLX5_FPGA_IMAGE_USER:
		return "user";
	case MLX5_FPGA_IMAGE_FACTORY:
		return "factory";
	default:
		return "unknown";
	}
}