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
struct btree_keys {struct bset_tree* set; } ;
struct bkey {int dummy; } ;
struct bset_tree {unsigned int size; struct bkey end; TYPE_1__* data; } ;
struct TYPE_2__ {struct bkey* start; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
 struct bkey* bkey_next (struct bkey*) ; 
 unsigned int bkey_to_cacheline (struct bset_tree*,struct bkey*) ; 
 struct bkey* bset_bkey_last (TYPE_1__*) ; 
 struct bset_tree* bset_tree_last (struct btree_keys*) ; 
 int /*<<< orphan*/  bset_written (struct btree_keys*,struct bset_tree*) ; 
 unsigned int inorder_to_tree (unsigned int,struct bset_tree*) ; 
 int /*<<< orphan*/  make_bfloat (struct bset_tree*,unsigned int) ; 
 struct bkey* tree_to_bkey (struct bset_tree*,unsigned int) ; 
 struct bkey* tree_to_prev_bkey (struct bset_tree*,unsigned int) ; 

void bch_bset_fix_invalidated_key(struct btree_keys *b, struct bkey *k)
{
	struct bset_tree *t;
	unsigned int inorder, j = 1;

	for (t = b->set; t <= bset_tree_last(b); t++)
		if (k < bset_bkey_last(t->data))
			goto found_set;

	BUG();
found_set:
	if (!t->size || !bset_written(b, t))
		return;

	inorder = bkey_to_cacheline(t, k);

	if (k == t->data->start)
		goto fix_left;

	if (bkey_next(k) == bset_bkey_last(t->data)) {
		t->end = *k;
		goto fix_right;
	}

	j = inorder_to_tree(inorder, t);

	if (j &&
	    j < t->size &&
	    k == tree_to_bkey(t, j))
fix_left:	do {
			make_bfloat(t, j);
			j = j * 2;
		} while (j < t->size);

	j = inorder_to_tree(inorder + 1, t);

	if (j &&
	    j < t->size &&
	    k == tree_to_prev_bkey(t, j))
fix_right:	do {
			make_bfloat(t, j);
			j = j * 2 + 1;
		} while (j < t->size);
}