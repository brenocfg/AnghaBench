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
struct btree_keys {struct bset_tree* set; } ;
struct bset_tree {scalar_t__ prev; scalar_t__ tree; int /*<<< orphan*/  size; } ;
struct bkey_float {int dummy; } ;
struct TYPE_2__ {scalar_t__ size; } ;

/* Variables and functions */
 int MAX_BSETS ; 
 unsigned int roundup (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void bset_alloc_tree(struct btree_keys *b, struct bset_tree *t)
{
	if (t != b->set) {
		unsigned int j = roundup(t[-1].size,
				     64 / sizeof(struct bkey_float));

		t->tree = t[-1].tree + j;
		t->prev = t[-1].prev + j;
	}

	while (t < b->set + MAX_BSETS)
		t++->size = 0;
}