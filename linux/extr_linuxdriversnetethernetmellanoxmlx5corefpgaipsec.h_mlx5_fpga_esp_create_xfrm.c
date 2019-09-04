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
struct mlx5_accel_esp_xfrm {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  EOPNOTSUPP ; 
 struct mlx5_accel_esp_xfrm* ERR_PTR (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline struct mlx5_accel_esp_xfrm *
mlx5_fpga_esp_create_xfrm(struct mlx5_core_dev *mdev,
			  const struct mlx5_accel_esp_xfrm_attrs *attrs,
			  u32 flags)
{
	return ERR_PTR(-EOPNOTSUPP);
}