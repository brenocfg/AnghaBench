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
struct TYPE_4__ {int start; int count; int /*<<< orphan*/  ida; } ;
struct TYPE_3__ {TYPE_2__ reserved_gids; } ;
struct mlx5_core_dev {TYPE_1__ roce; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int ida_simple_get (int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlx5_core_dbg (struct mlx5_core_dev*,char*,int) ; 

int mlx5_core_reserved_gid_alloc(struct mlx5_core_dev *dev, int *gid_index)
{
	int end = dev->roce.reserved_gids.start +
		  dev->roce.reserved_gids.count;
	int index = 0;

	index = ida_simple_get(&dev->roce.reserved_gids.ida,
			       dev->roce.reserved_gids.start, end,
			       GFP_KERNEL);
	if (index < 0)
		return index;

	mlx5_core_dbg(dev, "Allocating reserved GID %u\n", index);
	*gid_index = index;
	return 0;
}