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
struct closure {int dummy; } ;
struct TYPE_2__ {unsigned int nsets; } ;
struct btree {TYPE_1__ keys; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  __bch_btree_node_write (struct btree*,struct closure*) ; 
 int /*<<< orphan*/  bch_btree_init_next (struct btree*) ; 
 int /*<<< orphan*/  bch_btree_verify (struct btree*) ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 

void bch_btree_node_write(struct btree *b, struct closure *parent)
{
	unsigned int nsets = b->keys.nsets;

	lockdep_assert_held(&b->lock);

	__bch_btree_node_write(b, parent);

	/*
	 * do verify if there was more than one set initially (i.e. we did a
	 * sort) and we sorted down to a single set:
	 */
	if (nsets && !b->keys.nsets)
		bch_btree_verify(b);

	bch_btree_init_next(b);
}