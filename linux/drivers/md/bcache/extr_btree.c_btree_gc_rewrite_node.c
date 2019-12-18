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
struct keylist {int /*<<< orphan*/  top; } ;
struct btree_op {int dummy; } ;
struct btree {int /*<<< orphan*/  key; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int EINTR ; 
 int /*<<< orphan*/  bch_btree_insert_node (struct btree*,struct btree_op*,struct keylist*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bch_btree_node_write_sync (struct btree*) ; 
 int /*<<< orphan*/  bch_keylist_add (struct keylist*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bch_keylist_empty (struct keylist*) ; 
 int /*<<< orphan*/  bch_keylist_init (struct keylist*) ; 
 int /*<<< orphan*/  bch_keylist_push (struct keylist*) ; 
 scalar_t__ btree_check_reserve (struct btree*,int /*<<< orphan*/ *) ; 
 struct btree* btree_node_alloc_replacement (struct btree*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  btree_node_free (struct btree*) ; 
 int /*<<< orphan*/  make_btree_freeing_key (struct btree*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rw_unlock (int,struct btree*) ; 

__attribute__((used)) static int btree_gc_rewrite_node(struct btree *b, struct btree_op *op,
				 struct btree *replace)
{
	struct keylist keys;
	struct btree *n;

	if (btree_check_reserve(b, NULL))
		return 0;

	n = btree_node_alloc_replacement(replace, NULL);

	/* recheck reserve after allocating replacement node */
	if (btree_check_reserve(b, NULL)) {
		btree_node_free(n);
		rw_unlock(true, n);
		return 0;
	}

	bch_btree_node_write_sync(n);

	bch_keylist_init(&keys);
	bch_keylist_add(&keys, &n->key);

	make_btree_freeing_key(replace, keys.top);
	bch_keylist_push(&keys);

	bch_btree_insert_node(b, op, &keys, NULL, NULL);
	BUG_ON(!bch_keylist_empty(&keys));

	btree_node_free(replace);
	rw_unlock(true, n);

	/* Invalidated our iterator */
	return -EINTR;
}