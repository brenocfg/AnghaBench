#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ nsets; } ;
struct btree {scalar_t__ written; TYPE_1__* c; TYPE_2__ keys; scalar_t__ level; } ;
struct TYPE_5__ {int /*<<< orphan*/  sb; int /*<<< orphan*/  sort; } ;

/* Variables and functions */
 int /*<<< orphan*/  bch_bset_init_next (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bch_btree_sort (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bch_btree_sort_lazy (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bset_magic (int /*<<< orphan*/ *) ; 
 scalar_t__ btree_blocks (struct btree*) ; 
 int /*<<< orphan*/  write_block (struct btree*) ; 

__attribute__((used)) static void bch_btree_init_next(struct btree *b)
{
	/* If not a leaf node, always sort */
	if (b->level && b->keys.nsets)
		bch_btree_sort(&b->keys, &b->c->sort);
	else
		bch_btree_sort_lazy(&b->keys, &b->c->sort);

	if (b->written < btree_blocks(b))
		bch_bset_init_next(&b->keys, write_block(b),
				   bset_magic(&b->c->sb));

}