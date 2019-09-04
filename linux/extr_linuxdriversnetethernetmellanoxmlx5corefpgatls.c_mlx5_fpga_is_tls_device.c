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
struct mlx5_core_dev {int /*<<< orphan*/  fpga; } ;

/* Variables and functions */
 scalar_t__ MLX5_CAP_FPGA (struct mlx5_core_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MLX5_CAP_GEN (struct mlx5_core_dev*,int /*<<< orphan*/ ) ; 
 scalar_t__ MLX5_FPGA_CAP_SANDBOX_PRODUCT_ID_TLS ; 
 scalar_t__ MLX5_FPGA_CAP_SANDBOX_VENDOR_ID_MLNX ; 
 int /*<<< orphan*/  fpga ; 
 int /*<<< orphan*/  ieee_vendor_id ; 
 int /*<<< orphan*/  sandbox_product_id ; 
 int /*<<< orphan*/  sandbox_product_version ; 

bool mlx5_fpga_is_tls_device(struct mlx5_core_dev *mdev)
{
	if (!mdev->fpga || !MLX5_CAP_GEN(mdev, fpga))
		return false;

	if (MLX5_CAP_FPGA(mdev, ieee_vendor_id) !=
	    MLX5_FPGA_CAP_SANDBOX_VENDOR_ID_MLNX)
		return false;

	if (MLX5_CAP_FPGA(mdev, sandbox_product_id) !=
	    MLX5_FPGA_CAP_SANDBOX_PRODUCT_ID_TLS)
		return false;

	if (MLX5_CAP_FPGA(mdev, sandbox_product_version) != 0)
		return false;

	return true;
}