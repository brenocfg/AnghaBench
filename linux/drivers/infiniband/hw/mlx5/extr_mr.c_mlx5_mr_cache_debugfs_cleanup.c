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
struct TYPE_2__ {int /*<<< orphan*/ * root; } ;
struct mlx5_ib_dev {TYPE_1__ cache; scalar_t__ is_rep; } ;

/* Variables and functions */
 int /*<<< orphan*/  debugfs_remove_recursive (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mlx5_debugfs_root ; 

__attribute__((used)) static void mlx5_mr_cache_debugfs_cleanup(struct mlx5_ib_dev *dev)
{
	if (!mlx5_debugfs_root || dev->is_rep)
		return;

	debugfs_remove_recursive(dev->cache.root);
	dev->cache.root = NULL;
}