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
struct btree_keys {int dummy; } ;
struct btree_iter {struct btree_keys* b; scalar_t__ used; int /*<<< orphan*/  data; int /*<<< orphan*/  size; } ;
struct bset_tree {int /*<<< orphan*/  data; } ;
struct bkey {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 struct bkey* bch_bset_search (struct btree_keys*,struct bset_tree*,struct bkey*) ; 
 int /*<<< orphan*/  bch_btree_iter_push (struct btree_iter*,struct bkey*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bset_bkey_last (int /*<<< orphan*/ ) ; 
 struct bset_tree* bset_tree_last (struct btree_keys*) ; 

__attribute__((used)) static struct bkey *__bch_btree_iter_init(struct btree_keys *b,
					  struct btree_iter *iter,
					  struct bkey *search,
					  struct bset_tree *start)
{
	struct bkey *ret = NULL;

	iter->size = ARRAY_SIZE(iter->data);
	iter->used = 0;

#ifdef CONFIG_BCACHE_DEBUG
	iter->b = b;
#endif

	for (; start <= bset_tree_last(b); start++) {
		ret = bch_bset_search(b, start, search);
		bch_btree_iter_push(iter, ret, bset_bkey_last(start->data));
	}

	return ret;
}