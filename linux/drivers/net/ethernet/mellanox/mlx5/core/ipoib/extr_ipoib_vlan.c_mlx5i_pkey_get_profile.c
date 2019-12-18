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

/* Variables and functions */
 struct mlx5e_profile const mlx5i_pkey_nic_profile ; 

const struct mlx5e_profile *mlx5i_pkey_get_profile(void)
{
	return &mlx5i_pkey_nic_profile;
}