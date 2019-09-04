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
struct btree_keys {TYPE_1__* set; } ;
struct bset_tree {unsigned int size; unsigned int* prev; unsigned int tree; int /*<<< orphan*/  data; } ;
struct bkey {int dummy; } ;
struct TYPE_2__ {unsigned int tree; } ;

/* Variables and functions */
 struct bkey* bkey_next (struct bkey*) ; 
 unsigned int bkey_to_cacheline (struct bset_tree*,struct bkey*) ; 
 void* bkey_to_cacheline_offset (struct bset_tree*,unsigned int,struct bkey*) ; 
 unsigned int bkey_u64s (struct bkey*) ; 
 struct bkey* bset_bkey_last (int /*<<< orphan*/ ) ; 
 unsigned int btree_keys_cachelines (struct btree_keys*) ; 
 struct bkey* cacheline_to_bkey (struct bset_tree*,unsigned int,int /*<<< orphan*/ ) ; 
 struct bkey* table_to_bkey (struct bset_tree*,int) ; 

__attribute__((used)) static void bch_bset_fix_lookup_table(struct btree_keys *b,
				      struct bset_tree *t,
				      struct bkey *k)
{
	unsigned int shift = bkey_u64s(k);
	unsigned int j = bkey_to_cacheline(t, k);

	/* We're getting called from btree_split() or btree_gc, just bail out */
	if (!t->size)
		return;

	/*
	 * k is the key we just inserted; we need to find the entry in the
	 * lookup table for the first key that is strictly greater than k:
	 * it's either k's cacheline or the next one
	 */
	while (j < t->size &&
	       table_to_bkey(t, j) <= k)
		j++;

	/*
	 * Adjust all the lookup table entries, and find a new key for any that
	 * have gotten too big
	 */
	for (; j < t->size; j++) {
		t->prev[j] += shift;

		if (t->prev[j] > 7) {
			k = table_to_bkey(t, j - 1);

			while (k < cacheline_to_bkey(t, j, 0))
				k = bkey_next(k);

			t->prev[j] = bkey_to_cacheline_offset(t, j, k);
		}
	}

	if (t->size == b->set->tree + btree_keys_cachelines(b) - t->tree)
		return;

	/* Possibly add a new entry to the end of the lookup table */

	for (k = table_to_bkey(t, t->size - 1);
	     k != bset_bkey_last(t->data);
	     k = bkey_next(k))
		if (t->size == bkey_to_cacheline(t, k)) {
			t->prev[t->size] =
				bkey_to_cacheline_offset(t, t->size, k);
			t->size++;
		}
}