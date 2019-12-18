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
typedef  scalar_t__ u16 ;
struct mlx5_core_dev {int dummy; } ;

/* Variables and functions */
 scalar_t__ MLX5_SPECIAL_VPORTS (struct mlx5_core_dev const*) ; 
 scalar_t__ mlx5_core_max_vfs (struct mlx5_core_dev const*) ; 

u16 mlx5_eswitch_get_total_vports(const struct mlx5_core_dev *dev)
{
	return MLX5_SPECIAL_VPORTS(dev) + mlx5_core_max_vfs(dev);
}