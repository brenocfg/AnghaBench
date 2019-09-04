#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct mlx5_mr_cache {struct mlx5_cache_ent* ent; } ;
struct mlx5_ib_dev {struct mlx5_mr_cache cache; } ;
struct mlx5_cache_ent {scalar_t__ pending; } ;

/* Variables and functions */
 int MAX_MR_CACHE_ENTRIES ; 
 int /*<<< orphan*/  mlx5_ib_warn (struct mlx5_ib_dev*,char*,...) ; 
 int /*<<< orphan*/  msleep (int) ; 

__attribute__((used)) static void wait_for_async_commands(struct mlx5_ib_dev *dev)
{
	struct mlx5_mr_cache *cache = &dev->cache;
	struct mlx5_cache_ent *ent;
	int total = 0;
	int i;
	int j;

	for (i = 0; i < MAX_MR_CACHE_ENTRIES; i++) {
		ent = &cache->ent[i];
		for (j = 0 ; j < 1000; j++) {
			if (!ent->pending)
				break;
			msleep(50);
		}
	}
	for (i = 0; i < MAX_MR_CACHE_ENTRIES; i++) {
		ent = &cache->ent[i];
		total += ent->pending;
	}

	if (total)
		mlx5_ib_warn(dev, "aborted while there are %d pending mr requests\n", total);
	else
		mlx5_ib_warn(dev, "done with all pending requests\n");
}