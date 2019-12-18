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
struct btree_keys {int /*<<< orphan*/  page_order; struct bset_tree* set; } ;
struct bset_tree {int /*<<< orphan*/ * data; int /*<<< orphan*/ * tree; int /*<<< orphan*/ * prev; } ;

/* Variables and functions */
 scalar_t__ PAGE_SIZE ; 
 scalar_t__ bset_prev_bytes (struct btree_keys*) ; 
 scalar_t__ bset_tree_bytes (struct btree_keys*) ; 
 int /*<<< orphan*/  free_pages (unsigned long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_order (scalar_t__) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 

void bch_btree_keys_free(struct btree_keys *b)
{
	struct bset_tree *t = b->set;

	if (bset_prev_bytes(b) < PAGE_SIZE)
		kfree(t->prev);
	else
		free_pages((unsigned long) t->prev,
			   get_order(bset_prev_bytes(b)));

	if (bset_tree_bytes(b) < PAGE_SIZE)
		kfree(t->tree);
	else
		free_pages((unsigned long) t->tree,
			   get_order(bset_tree_bytes(b)));

	free_pages((unsigned long) t->data, b->page_order);

	t->prev = NULL;
	t->tree = NULL;
	t->data = NULL;
}