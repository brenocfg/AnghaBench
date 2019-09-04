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
typedef  int /*<<< orphan*/  u32 ;
struct mlx5_core_dev {int dummy; } ;
struct mlx5_accel_esp_xfrm_attrs {int dummy; } ;
struct mlx5_accel_esp_xfrm {struct mlx5_core_dev* mdev; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct mlx5_accel_esp_xfrm*) ; 
 struct mlx5_accel_esp_xfrm* mlx5_fpga_esp_create_xfrm (struct mlx5_core_dev*,struct mlx5_accel_esp_xfrm_attrs const*,int /*<<< orphan*/ ) ; 

struct mlx5_accel_esp_xfrm *
mlx5_accel_esp_create_xfrm(struct mlx5_core_dev *mdev,
			   const struct mlx5_accel_esp_xfrm_attrs *attrs,
			   u32 flags)
{
	struct mlx5_accel_esp_xfrm *xfrm;

	xfrm = mlx5_fpga_esp_create_xfrm(mdev, attrs, flags);
	if (IS_ERR(xfrm))
		return xfrm;

	xfrm->mdev = mdev;
	return xfrm;
}