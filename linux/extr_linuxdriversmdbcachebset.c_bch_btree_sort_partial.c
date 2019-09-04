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
struct btree_keys {size_t page_order; unsigned int nsets; TYPE_2__* set; } ;
struct btree_iter {int dummy; } ;
struct bset_sort_state {int dummy; } ;
struct TYPE_4__ {TYPE_1__* data; } ;
struct TYPE_3__ {scalar_t__ keys; } ;

/* Variables and functions */
 int /*<<< orphan*/  EBUG_ON (int) ; 
 int /*<<< orphan*/  __bch_btree_iter_init (struct btree_keys*,struct btree_iter*,int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  __btree_sort (struct btree_keys*,struct btree_iter*,unsigned int,size_t,int,struct bset_sort_state*) ; 
 int /*<<< orphan*/  __set_bytes (TYPE_1__*,size_t) ; 
 int bch_count_data (struct btree_keys*) ; 
 size_t get_order (int /*<<< orphan*/ ) ; 

void bch_btree_sort_partial(struct btree_keys *b, unsigned int start,
			    struct bset_sort_state *state)
{
	size_t order = b->page_order, keys = 0;
	struct btree_iter iter;
	int oldsize = bch_count_data(b);

	__bch_btree_iter_init(b, &iter, NULL, &b->set[start]);

	if (start) {
		unsigned int i;

		for (i = start; i <= b->nsets; i++)
			keys += b->set[i].data->keys;

		order = get_order(__set_bytes(b->set->data, keys));
	}

	__btree_sort(b, &iter, start, order, false, state);

	EBUG_ON(oldsize >= 0 && bch_count_data(b) != oldsize);
}