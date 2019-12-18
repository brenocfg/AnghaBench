#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct mlx5_pme_stats {int dummy; } ;
struct TYPE_4__ {TYPE_1__* events; } ;
struct mlx5_core_dev {TYPE_2__ priv; } ;
struct TYPE_3__ {struct mlx5_pme_stats pme_stats; } ;

/* Variables and functions */

void mlx5_get_pme_stats(struct mlx5_core_dev *dev, struct mlx5_pme_stats *stats)
{
	*stats = dev->priv.events->pme_stats;
}