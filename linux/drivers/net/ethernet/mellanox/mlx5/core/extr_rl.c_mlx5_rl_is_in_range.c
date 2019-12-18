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
typedef  scalar_t__ u32 ;
struct mlx5_rl_table {scalar_t__ max_rate; scalar_t__ min_rate; } ;
struct TYPE_2__ {struct mlx5_rl_table rl_table; } ;
struct mlx5_core_dev {TYPE_1__ priv; } ;

/* Variables and functions */

bool mlx5_rl_is_in_range(struct mlx5_core_dev *dev, u32 rate)
{
	struct mlx5_rl_table *table = &dev->priv.rl_table;

	return (rate <= table->max_rate && rate >= table->min_rate);
}