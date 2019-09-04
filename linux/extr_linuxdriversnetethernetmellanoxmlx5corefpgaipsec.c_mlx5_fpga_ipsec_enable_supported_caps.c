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
typedef  int u32 ;
struct mlx5_core_dev {int dummy; } ;

/* Variables and functions */
 int MLX5_ACCEL_IPSEC_CAP_RX_NO_TRAILER ; 
 int MLX5_FPGA_IPSEC_CAP_NO_TRAILER ; 
 int mlx5_fpga_ipsec_device_caps (struct mlx5_core_dev*) ; 
 int mlx5_fpga_ipsec_set_caps (struct mlx5_core_dev*,int) ; 

__attribute__((used)) static int mlx5_fpga_ipsec_enable_supported_caps(struct mlx5_core_dev *mdev)
{
	u32 dev_caps = mlx5_fpga_ipsec_device_caps(mdev);
	u32 flags = 0;

	if (dev_caps & MLX5_ACCEL_IPSEC_CAP_RX_NO_TRAILER)
		flags |= MLX5_FPGA_IPSEC_CAP_NO_TRAILER;

	return mlx5_fpga_ipsec_set_caps(mdev, flags);
}