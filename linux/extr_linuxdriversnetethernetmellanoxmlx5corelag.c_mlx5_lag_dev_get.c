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
struct mlx5_lag {int dummy; } ;
struct TYPE_2__ {struct mlx5_lag* lag; } ;
struct mlx5_core_dev {TYPE_1__ priv; } ;

/* Variables and functions */

__attribute__((used)) static struct mlx5_lag *mlx5_lag_dev_get(struct mlx5_core_dev *dev)
{
	return dev->priv.lag;
}