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
typedef  int /*<<< orphan*/  btree_map_keys_fn ;

/* Variables and functions */
 int btree_root (int /*<<< orphan*/ ,struct cache_set*,struct btree_op*,struct bkey*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  map_keys_recurse ; 

int bch_btree_map_keys(struct btree_op *op, struct cache_set *c,
		       struct bkey *from, btree_map_keys_fn *fn, int flags)
{
	return btree_root(map_keys_recurse, c, op, from, fn, flags);
}