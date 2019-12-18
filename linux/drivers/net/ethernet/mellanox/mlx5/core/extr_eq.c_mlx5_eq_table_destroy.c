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
 int /*<<< orphan*/  destroy_async_eqs (struct mlx5_core_dev*) ; 
 int /*<<< orphan*/  destroy_comp_eqs (struct mlx5_core_dev*) ; 

void mlx5_eq_table_destroy(struct mlx5_core_dev *dev)
{
	destroy_comp_eqs(dev);
	destroy_async_eqs(dev);
}