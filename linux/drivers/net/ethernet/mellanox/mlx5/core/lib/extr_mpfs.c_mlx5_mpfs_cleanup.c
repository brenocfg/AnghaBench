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
struct mlx5_mpfs {int /*<<< orphan*/  bitmap; int /*<<< orphan*/  hash; } ;
struct TYPE_2__ {struct mlx5_mpfs* mpfs; } ;
struct mlx5_core_dev {TYPE_1__ priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  MLX5_ESWITCH_MANAGER (struct mlx5_core_dev*) ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  bitmap_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hlist_empty (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct mlx5_mpfs*) ; 

void mlx5_mpfs_cleanup(struct mlx5_core_dev *dev)
{
	struct mlx5_mpfs *mpfs = dev->priv.mpfs;

	if (!MLX5_ESWITCH_MANAGER(dev))
		return;

	WARN_ON(!hlist_empty(mpfs->hash));
	bitmap_free(mpfs->bitmap);
	kfree(mpfs);
}