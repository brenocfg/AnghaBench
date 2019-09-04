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
struct btree_keys {int /*<<< orphan*/  page_order; } ;
struct btree_iter {int dummy; } ;
struct bset_sort_state {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  __btree_sort (struct btree_keys*,struct btree_iter*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,struct bset_sort_state*) ; 

void bch_btree_sort_and_fix_extents(struct btree_keys *b,
				    struct btree_iter *iter,
				    struct bset_sort_state *state)
{
	__btree_sort(b, iter, 0, b->page_order, true, state);
}