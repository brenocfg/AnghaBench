#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint64_t ;
struct btree_keys {int page_order; int /*<<< orphan*/  last_set_unwritten; } ;
struct bset_tree {TYPE_1__* data; } ;
struct bkey {int dummy; } ;
struct TYPE_4__ {int keys; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 scalar_t__ PAGE_SIZE ; 
 scalar_t__ __set_bytes (TYPE_1__*,int) ; 
 int /*<<< orphan*/  bch_bset_fix_lookup_table (struct btree_keys*,struct bset_tree*,struct bkey*) ; 
 int /*<<< orphan*/  bkey_copy (struct bkey*,struct bkey*) ; 
 int bkey_u64s (struct bkey*) ; 
 scalar_t__ bset_bkey_last (TYPE_1__*) ; 
 scalar_t__ bset_byte_offset (struct btree_keys*,TYPE_1__*) ; 
 struct bset_tree* bset_tree_last (struct btree_keys*) ; 
 int /*<<< orphan*/  memmove (int /*<<< orphan*/ *,struct bkey*,int) ; 

void bch_bset_insert(struct btree_keys *b, struct bkey *where,
		     struct bkey *insert)
{
	struct bset_tree *t = bset_tree_last(b);

	BUG_ON(!b->last_set_unwritten);
	BUG_ON(bset_byte_offset(b, t->data) +
	       __set_bytes(t->data, t->data->keys + bkey_u64s(insert)) >
	       PAGE_SIZE << b->page_order);

	memmove((uint64_t *) where + bkey_u64s(insert),
		where,
		(void *) bset_bkey_last(t->data) - (void *) where);

	t->data->keys += bkey_u64s(insert);
	bkey_copy(where, insert);
	bch_bset_fix_lookup_table(b, t, where);
}