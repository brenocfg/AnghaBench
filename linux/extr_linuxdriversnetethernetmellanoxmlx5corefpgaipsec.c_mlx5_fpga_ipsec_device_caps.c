#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct mlx5_fpga_device {TYPE_1__* ipsec; } ;
struct mlx5_core_dev {struct mlx5_fpga_device* fpga; } ;
struct TYPE_2__ {int /*<<< orphan*/  caps; } ;

/* Variables and functions */
 int /*<<< orphan*/  MLX5_ACCEL_IPSEC_CAP_DEVICE ; 
 int /*<<< orphan*/  MLX5_ACCEL_IPSEC_CAP_ESN ; 
 int /*<<< orphan*/  MLX5_ACCEL_IPSEC_CAP_ESP ; 
 int /*<<< orphan*/  MLX5_ACCEL_IPSEC_CAP_IPV6 ; 
 int /*<<< orphan*/  MLX5_ACCEL_IPSEC_CAP_LSO ; 
 int /*<<< orphan*/  MLX5_ACCEL_IPSEC_CAP_REQUIRED_METADATA ; 
 int /*<<< orphan*/  MLX5_ACCEL_IPSEC_CAP_RX_NO_TRAILER ; 
 int /*<<< orphan*/  MLX5_ACCEL_IPSEC_CAP_TX_IV_IS_ESN ; 
 scalar_t__ MLX5_GET (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  esn ; 
 int /*<<< orphan*/  esp ; 
 int /*<<< orphan*/  ipsec_extended_cap ; 
 int /*<<< orphan*/  ipv6 ; 
 int /*<<< orphan*/  lso ; 
 scalar_t__ mlx5_fpga_is_ipsec_device (struct mlx5_core_dev*) ; 
 int /*<<< orphan*/  rx_no_trailer ; 

u32 mlx5_fpga_ipsec_device_caps(struct mlx5_core_dev *mdev)
{
	struct mlx5_fpga_device *fdev = mdev->fpga;
	u32 ret = 0;

	if (mlx5_fpga_is_ipsec_device(mdev)) {
		ret |= MLX5_ACCEL_IPSEC_CAP_DEVICE;
		ret |= MLX5_ACCEL_IPSEC_CAP_REQUIRED_METADATA;
	} else {
		return ret;
	}

	if (!fdev->ipsec)
		return ret;

	if (MLX5_GET(ipsec_extended_cap, fdev->ipsec->caps, esp))
		ret |= MLX5_ACCEL_IPSEC_CAP_ESP;

	if (MLX5_GET(ipsec_extended_cap, fdev->ipsec->caps, ipv6))
		ret |= MLX5_ACCEL_IPSEC_CAP_IPV6;

	if (MLX5_GET(ipsec_extended_cap, fdev->ipsec->caps, lso))
		ret |= MLX5_ACCEL_IPSEC_CAP_LSO;

	if (MLX5_GET(ipsec_extended_cap, fdev->ipsec->caps, rx_no_trailer))
		ret |= MLX5_ACCEL_IPSEC_CAP_RX_NO_TRAILER;

	if (MLX5_GET(ipsec_extended_cap, fdev->ipsec->caps, esn)) {
		ret |= MLX5_ACCEL_IPSEC_CAP_ESN;
		ret |= MLX5_ACCEL_IPSEC_CAP_TX_IV_IS_ESN;
	}

	return ret;
}