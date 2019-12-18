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
struct TYPE_3__ {unsigned int start; scalar_t__ count; int /*<<< orphan*/  ida; } ;
struct TYPE_4__ {TYPE_1__ reserved_gids; } ;
struct mlx5_core_dev {TYPE_2__ roce; } ;

/* Variables and functions */
 unsigned int MLX5_CAP_ROCE (struct mlx5_core_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ida_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  roce_address_table_size ; 

void mlx5_init_reserved_gids(struct mlx5_core_dev *dev)
{
	unsigned int tblsz = MLX5_CAP_ROCE(dev, roce_address_table_size);

	ida_init(&dev->roce.reserved_gids.ida);
	dev->roce.reserved_gids.start = tblsz;
	dev->roce.reserved_gids.count = 0;
}