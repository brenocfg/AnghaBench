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
struct mlx5_core_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  mlx5_error_sw_reset (struct mlx5_core_dev*) ; 
 int /*<<< orphan*/  mlx5_unload_one (struct mlx5_core_dev*,int) ; 

void mlx5_disable_device(struct mlx5_core_dev *dev)
{
	mlx5_error_sw_reset(dev);
	mlx5_unload_one(dev, false);
}