#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct btree_keys {int last_set_unwritten; TYPE_2__* set; } ;
struct bset_tree {scalar_t__ tree; int size; TYPE_1__* data; int /*<<< orphan*/ * prev; } ;
struct TYPE_4__ {scalar_t__ tree; } ;
struct TYPE_3__ {int /*<<< orphan*/  start; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  bkey_to_cacheline_offset (struct bset_tree*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bset_alloc_tree (struct btree_keys*,struct bset_tree*) ; 
 struct bset_tree* bset_tree_last (struct btree_keys*) ; 
 scalar_t__ btree_keys_cachelines (struct btree_keys*) ; 

__attribute__((used)) static void bch_bset_build_unwritten_tree(struct btree_keys *b)
{
	struct bset_tree *t = bset_tree_last(b);

	BUG_ON(b->last_set_unwritten);
	b->last_set_unwritten = 1;

	bset_alloc_tree(b, t);

	if (t->tree != b->set->tree + btree_keys_cachelines(b)) {
		t->prev[0] = bkey_to_cacheline_offset(t, 0, t->data->start);
		t->size = 1;
	}
}