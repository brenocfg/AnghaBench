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
struct TYPE_3__ {unsigned int count; unsigned int start; } ;
struct TYPE_4__ {TYPE_1__ reserved_gids; } ;
struct mlx5_core_dev {TYPE_2__ roce; int /*<<< orphan*/  intf_state; } ;

/* Variables and functions */
 int /*<<< orphan*/  MLX5_INTERFACE_STATE_UP ; 
 int /*<<< orphan*/  WARN (int,char*,...) ; 
 int /*<<< orphan*/  mlx5_core_dbg (struct mlx5_core_dev*,char*,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void mlx5_core_unreserve_gids(struct mlx5_core_dev *dev, unsigned int count)
{
	WARN(test_bit(MLX5_INTERFACE_STATE_UP, &dev->intf_state), "Unreserving GIDs when interfaces are up");
	WARN(count > dev->roce.reserved_gids.count, "Unreserving %u GIDs when only %u reserved",
	     count, dev->roce.reserved_gids.count);

	dev->roce.reserved_gids.start += count;
	dev->roce.reserved_gids.count -= count;
	mlx5_core_dbg(dev, "%u GIDs starting at %u left reserved\n",
		      dev->roce.reserved_gids.count,
		      dev->roce.reserved_gids.start);
}