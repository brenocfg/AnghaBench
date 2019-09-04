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
struct TYPE_3__ {int /*<<< orphan*/  ida; } ;
struct TYPE_4__ {TYPE_1__ reserved_gids; } ;
struct mlx5_core_dev {TYPE_2__ roce; } ;

/* Variables and functions */
 int /*<<< orphan*/  ida_simple_remove (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  mlx5_core_dbg (struct mlx5_core_dev*,char*,int) ; 

void mlx5_core_reserved_gid_free(struct mlx5_core_dev *dev, int gid_index)
{
	mlx5_core_dbg(dev, "Freeing reserved GID %u\n", gid_index);
	ida_simple_remove(&dev->roce.reserved_gids.ida, gid_index);
}