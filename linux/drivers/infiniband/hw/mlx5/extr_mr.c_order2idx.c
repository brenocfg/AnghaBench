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
struct mlx5_mr_cache {TYPE_1__* ent; } ;
struct mlx5_ib_dev {struct mlx5_mr_cache cache; } ;
struct TYPE_2__ {int order; } ;

/* Variables and functions */

__attribute__((used)) static int order2idx(struct mlx5_ib_dev *dev, int order)
{
	struct mlx5_mr_cache *cache = &dev->cache;

	if (order < cache->ent[0].order)
		return 0;
	else
		return order - cache->ent[0].order;
}