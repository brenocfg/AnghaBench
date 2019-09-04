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
struct mlx5_ib_dev {int /*<<< orphan*/  port; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlx5_ib_cleanup_multiport_master (struct mlx5_ib_dev*) ; 

void mlx5_ib_stage_init_cleanup(struct mlx5_ib_dev *dev)
{
	mlx5_ib_cleanup_multiport_master(dev);
#ifdef CONFIG_INFINIBAND_ON_DEMAND_PAGING
	cleanup_srcu_struct(&dev->mr_srcu);
#endif
	kfree(dev->port);
}