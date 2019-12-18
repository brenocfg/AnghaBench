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
typedef  int /*<<< orphan*/  uint64_t ;
struct btree_keys {unsigned int nsets; struct bset_tree* set; } ;
struct bset_tree {int size; TYPE_2__* tree; TYPE_1__* data; } ;
struct bset_stats {size_t bytes_written; size_t bytes_unwritten; int /*<<< orphan*/  sets_unwritten; int /*<<< orphan*/  failed; int /*<<< orphan*/  floats; int /*<<< orphan*/  sets_written; } ;
struct TYPE_4__ {int exponent; } ;
struct TYPE_3__ {int keys; } ;

/* Variables and functions */
 scalar_t__ bset_written (struct btree_keys*,struct bset_tree*) ; 

void bch_btree_keys_stats(struct btree_keys *b, struct bset_stats *stats)
{
	unsigned int i;

	for (i = 0; i <= b->nsets; i++) {
		struct bset_tree *t = &b->set[i];
		size_t bytes = t->data->keys * sizeof(uint64_t);
		size_t j;

		if (bset_written(b, t)) {
			stats->sets_written++;
			stats->bytes_written += bytes;

			stats->floats += t->size - 1;

			for (j = 1; j < t->size; j++)
				if (t->tree[j].exponent == 127)
					stats->failed++;
		} else {
			stats->sets_unwritten++;
			stats->bytes_unwritten += bytes;
		}
	}
}