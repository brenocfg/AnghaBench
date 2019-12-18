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
struct mlx5e_profile {int dummy; } ;
struct mlx5_core_dev {int dummy; } ;

/* Variables and functions */
 scalar_t__ mlx5_is_sub_interface (struct mlx5_core_dev*) ; 
 struct mlx5e_profile const mlx5i_nic_profile ; 
 struct mlx5e_profile const* mlx5i_pkey_get_profile () ; 

__attribute__((used)) static const struct mlx5e_profile *mlx5_get_profile(struct mlx5_core_dev *mdev)
{
	if (mlx5_is_sub_interface(mdev))
		return mlx5i_pkey_get_profile();
	return &mlx5i_nic_profile;
}