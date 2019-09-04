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
struct mlx5_mr_cache {void* root; struct mlx5_cache_ent* ent; } ;
struct mlx5_ib_dev {TYPE_2__* mdev; scalar_t__ rep; struct mlx5_mr_cache cache; } ;
struct mlx5_cache_ent {char* name; int order; void* fmiss; int /*<<< orphan*/  miss; void* dir; void* fcur; int /*<<< orphan*/  cur; void* flimit; void* fsize; } ;
struct TYPE_3__ {void* dbg_root; } ;
struct TYPE_4__ {TYPE_1__ priv; } ;

/* Variables and functions */
 int ENOMEM ; 
 int MAX_MR_CACHE_ENTRIES ; 
 void* debugfs_create_dir (char*,void*) ; 
 void* debugfs_create_file (char*,int,void*,struct mlx5_cache_ent*,int /*<<< orphan*/ *) ; 
 void* debugfs_create_u32 (char*,int,void*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  limit_fops ; 
 int /*<<< orphan*/  mlx5_debugfs_root ; 
 int /*<<< orphan*/  mlx5_mr_cache_debugfs_cleanup (struct mlx5_ib_dev*) ; 
 int /*<<< orphan*/  size_fops ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 

__attribute__((used)) static int mlx5_mr_cache_debugfs_init(struct mlx5_ib_dev *dev)
{
	struct mlx5_mr_cache *cache = &dev->cache;
	struct mlx5_cache_ent *ent;
	int i;

	if (!mlx5_debugfs_root || dev->rep)
		return 0;

	cache->root = debugfs_create_dir("mr_cache", dev->mdev->priv.dbg_root);
	if (!cache->root)
		return -ENOMEM;

	for (i = 0; i < MAX_MR_CACHE_ENTRIES; i++) {
		ent = &cache->ent[i];
		sprintf(ent->name, "%d", ent->order);
		ent->dir = debugfs_create_dir(ent->name,  cache->root);
		if (!ent->dir)
			goto err;

		ent->fsize = debugfs_create_file("size", 0600, ent->dir, ent,
						 &size_fops);
		if (!ent->fsize)
			goto err;

		ent->flimit = debugfs_create_file("limit", 0600, ent->dir, ent,
						  &limit_fops);
		if (!ent->flimit)
			goto err;

		ent->fcur = debugfs_create_u32("cur", 0400, ent->dir,
					       &ent->cur);
		if (!ent->fcur)
			goto err;

		ent->fmiss = debugfs_create_u32("miss", 0600, ent->dir,
						&ent->miss);
		if (!ent->fmiss)
			goto err;
	}

	return 0;
err:
	mlx5_mr_cache_debugfs_cleanup(dev);

	return -ENOMEM;
}