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
struct btree_keys_ops {int dummy; } ;
struct btree_keys {int* expensive_debug_checks; TYPE_1__* set; scalar_t__ last_set_unwritten; scalar_t__ nsets; struct btree_keys_ops const* ops; } ;
struct TYPE_2__ {int /*<<< orphan*/ * data; scalar_t__ size; } ;

/* Variables and functions */
 unsigned int MAX_BSETS ; 

void bch_btree_keys_init(struct btree_keys *b, const struct btree_keys_ops *ops,
			 bool *expensive_debug_checks)
{
	unsigned int i;

	b->ops = ops;
	b->expensive_debug_checks = expensive_debug_checks;
	b->nsets = 0;
	b->last_set_unwritten = 0;

	/* XXX: shouldn't be needed */
	for (i = 0; i < MAX_BSETS; i++)
		b->set[i].size = 0;
	/*
	 * Second loop starts at 1 because b->keys[0]->data is the memory we
	 * allocated
	 */
	for (i = 1; i < MAX_BSETS; i++)
		b->set[i].data = NULL;
}