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
struct regmap {int dummy; } ;
struct regcache_rbtree_node {int /*<<< orphan*/  block; int /*<<< orphan*/  cache_present; } ;

/* Variables and functions */
 int /*<<< orphan*/  regcache_set_val (struct regmap*,int /*<<< orphan*/ ,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  set_bit (unsigned int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void regcache_rbtree_set_register(struct regmap *map,
					 struct regcache_rbtree_node *rbnode,
					 unsigned int idx, unsigned int val)
{
	set_bit(idx, rbnode->cache_present);
	regcache_set_val(map, rbnode->block, idx, val);
}