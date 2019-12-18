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
struct TYPE_3__ {int /*<<< orphan*/  ida; scalar_t__ count; scalar_t__ start; } ;
struct TYPE_4__ {TYPE_1__ reserved_gids; } ;
struct mlx5_core_dev {TYPE_2__ roce; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  ida_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ida_is_empty (int /*<<< orphan*/ *) ; 

void mlx5_cleanup_reserved_gids(struct mlx5_core_dev *dev)
{
	WARN_ON(!ida_is_empty(&dev->roce.reserved_gids.ida));
	dev->roce.reserved_gids.start = 0;
	dev->roce.reserved_gids.count = 0;
	ida_destroy(&dev->roce.reserved_gids.ida);
}