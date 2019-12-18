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
struct mlx5_mpfs {int size; int /*<<< orphan*/  bitmap; int /*<<< orphan*/  lock; } ;
struct TYPE_2__ {struct mlx5_mpfs* mpfs; } ;
struct mlx5_core_dev {TYPE_1__ priv; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int MLX5_CAP_GEN (struct mlx5_core_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MLX5_ESWITCH_MANAGER (struct mlx5_core_dev*) ; 
 int /*<<< orphan*/  bitmap_zalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct mlx5_mpfs*) ; 
 struct mlx5_mpfs* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  log_max_l2_table ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 

int mlx5_mpfs_init(struct mlx5_core_dev *dev)
{
	int l2table_size = 1 << MLX5_CAP_GEN(dev, log_max_l2_table);
	struct mlx5_mpfs *mpfs;

	if (!MLX5_ESWITCH_MANAGER(dev))
		return 0;

	mpfs = kzalloc(sizeof(*mpfs), GFP_KERNEL);
	if (!mpfs)
		return -ENOMEM;

	mutex_init(&mpfs->lock);
	mpfs->size   = l2table_size;
	mpfs->bitmap = bitmap_zalloc(l2table_size, GFP_KERNEL);
	if (!mpfs->bitmap) {
		kfree(mpfs);
		return -ENOMEM;
	}

	dev->priv.mpfs = mpfs;
	return 0;
}