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

/* Variables and functions */
 int /*<<< orphan*/  mlx5_register_interface (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mlx5e_build_ptys2ethtool_map () ; 
 int /*<<< orphan*/  mlx5e_interface ; 
 int /*<<< orphan*/  mlx5e_ipsec_build_inverse_table () ; 

void mlx5e_init(void)
{
	mlx5e_ipsec_build_inverse_table();
	mlx5e_build_ptys2ethtool_map();
	mlx5_register_interface(&mlx5e_interface);
}