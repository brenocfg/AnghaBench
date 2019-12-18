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
struct btree {int dummy; } ;

/* Variables and functions */
 struct btree* __bch_btree_node_alloc (struct cache_set*,struct btree_op*,int,int /*<<< orphan*/ ,struct btree*) ; 

__attribute__((used)) static struct btree *bch_btree_node_alloc(struct cache_set *c,
					  struct btree_op *op, int level,
					  struct btree *parent)
{
	return __bch_btree_node_alloc(c, op, level, op != NULL, parent);
}