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
struct btree_keys_ops {int dummy; } ;
struct btree_keys {int* expensive_debug_checks; scalar_t__ last_set_unwritten; scalar_t__ nsets; struct btree_keys_ops const* ops; } ;

/* Variables and functions */

void bch_btree_keys_init(struct btree_keys *b, const struct btree_keys_ops *ops,
			 bool *expensive_debug_checks)
{
	b->ops = ops;
	b->expensive_debug_checks = expensive_debug_checks;
	b->nsets = 0;
	b->last_set_unwritten = 0;

	/*
	 * struct btree_keys in embedded in struct btree, and struct
	 * bset_tree is embedded into struct btree_keys. They are all
	 * initialized as 0 by kzalloc() in mca_bucket_alloc(), and
	 * b->set[0].data is allocated in bch_btree_keys_alloc(), so we
	 * don't have to initiate b->set[].size and b->set[].data here
	 * any more.
	 */
}