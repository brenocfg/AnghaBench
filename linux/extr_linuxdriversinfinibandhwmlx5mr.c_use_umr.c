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
struct mlx5_ib_dev {int dummy; } ;

/* Variables and functions */
 int mr_cache_max_order (struct mlx5_ib_dev*) ; 
 scalar_t__ umr_can_modify_entity_size (struct mlx5_ib_dev*) ; 

__attribute__((used)) static bool use_umr(struct mlx5_ib_dev *dev, int order)
{
	return order <= mr_cache_max_order(dev) &&
		umr_can_modify_entity_size(dev);
}