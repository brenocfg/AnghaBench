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
struct TYPE_2__ {int /*<<< orphan*/  memic_alloc_pages; } ;
struct mlx5_ib_dev {TYPE_1__ dm; int /*<<< orphan*/  mr_srcu; } ;

/* Variables and functions */
 int /*<<< orphan*/  CONFIG_INFINIBAND_ON_DEMAND_PAGING ; 
 scalar_t__ IS_ENABLED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MLX5_MAX_MEMIC_PAGES ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  bitmap_empty (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cleanup_srcu_struct (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mlx5_ib_cleanup_multiport_master (struct mlx5_ib_dev*) ; 
 int /*<<< orphan*/  srcu_barrier (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void mlx5_ib_stage_init_cleanup(struct mlx5_ib_dev *dev)
{
	mlx5_ib_cleanup_multiport_master(dev);
	if (IS_ENABLED(CONFIG_INFINIBAND_ON_DEMAND_PAGING)) {
		srcu_barrier(&dev->mr_srcu);
		cleanup_srcu_struct(&dev->mr_srcu);
	}

	WARN_ON(!bitmap_empty(dev->dm.memic_alloc_pages, MLX5_MAX_MEMIC_PAGES));
}