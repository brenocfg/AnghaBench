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
struct regmap {int num_reg_defaults; TYPE_1__* reg_defaults; struct regcache_rbtree_ctx* cache; } ;
struct regcache_rbtree_ctx {int /*<<< orphan*/ * cached_rbnode; int /*<<< orphan*/  root; } ;
struct TYPE_2__ {int /*<<< orphan*/  def; int /*<<< orphan*/  reg; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  RB_ROOT ; 
 struct regcache_rbtree_ctx* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  regcache_rbtree_exit (struct regmap*) ; 
 int regcache_rbtree_write (struct regmap*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int regcache_rbtree_init(struct regmap *map)
{
	struct regcache_rbtree_ctx *rbtree_ctx;
	int i;
	int ret;

	map->cache = kmalloc(sizeof *rbtree_ctx, GFP_KERNEL);
	if (!map->cache)
		return -ENOMEM;

	rbtree_ctx = map->cache;
	rbtree_ctx->root = RB_ROOT;
	rbtree_ctx->cached_rbnode = NULL;

	for (i = 0; i < map->num_reg_defaults; i++) {
		ret = regcache_rbtree_write(map,
					    map->reg_defaults[i].reg,
					    map->reg_defaults[i].def);
		if (ret)
			goto err;
	}

	return 0;

err:
	regcache_rbtree_exit(map);
	return ret;
}