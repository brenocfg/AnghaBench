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
struct regmap {int reg_stride; } ;
struct regcache_rbtree_node {unsigned int base_reg; int blklen; } ;

/* Variables and functions */

__attribute__((used)) static inline void regcache_rbtree_get_base_top_reg(
	struct regmap *map,
	struct regcache_rbtree_node *rbnode,
	unsigned int *base, unsigned int *top)
{
	*base = rbnode->base_reg;
	*top = rbnode->base_reg + ((rbnode->blklen - 1) * map->reg_stride);
}