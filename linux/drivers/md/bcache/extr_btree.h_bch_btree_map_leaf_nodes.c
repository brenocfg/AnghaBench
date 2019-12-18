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
struct cache_set {int dummy; } ;
struct btree_op {int dummy; } ;
struct bkey {int dummy; } ;
typedef  int /*<<< orphan*/  btree_map_nodes_fn ;

/* Variables and functions */
 int /*<<< orphan*/  MAP_LEAF_NODES ; 
 int __bch_btree_map_nodes (struct btree_op*,struct cache_set*,struct bkey*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int bch_btree_map_leaf_nodes(struct btree_op *op,
					   struct cache_set *c,
					   struct bkey *from,
					   btree_map_nodes_fn *fn)
{
	return __bch_btree_map_nodes(op, c, from, fn, MAP_LEAF_NODES);
}