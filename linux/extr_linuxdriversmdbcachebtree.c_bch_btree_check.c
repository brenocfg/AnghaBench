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

/* Variables and functions */
 int /*<<< orphan*/  SHRT_MAX ; 
 int /*<<< orphan*/  bch_btree_op_init (struct btree_op*,int /*<<< orphan*/ ) ; 
 int btree_root (int /*<<< orphan*/ ,struct cache_set*,struct btree_op*) ; 
 int /*<<< orphan*/  check_recurse ; 

int bch_btree_check(struct cache_set *c)
{
	struct btree_op op;

	bch_btree_op_init(&op, SHRT_MAX);

	return btree_root(check_recurse, c, &op);
}