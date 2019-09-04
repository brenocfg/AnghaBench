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
struct mlx4_dev {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  bitmap; } ;
struct TYPE_4__ {TYPE_1__ cq_table; } ;

/* Variables and functions */
 int /*<<< orphan*/  mlx4_bitmap_cleanup (int /*<<< orphan*/ *) ; 
 scalar_t__ mlx4_is_slave (struct mlx4_dev*) ; 
 TYPE_2__* mlx4_priv (struct mlx4_dev*) ; 

void mlx4_cleanup_cq_table(struct mlx4_dev *dev)
{
	if (mlx4_is_slave(dev))
		return;
	/* Nothing to do to clean up radix_tree */
	mlx4_bitmap_cleanup(&mlx4_priv(dev)->cq_table.bitmap);
}