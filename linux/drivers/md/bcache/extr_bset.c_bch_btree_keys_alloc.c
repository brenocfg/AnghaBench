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
struct btree_keys {unsigned int page_order; struct bset_tree* set; } ;
struct bset_tree {void* prev; void* tree; void* data; } ;
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (void*) ; 
 int ENOMEM ; 
 scalar_t__ PAGE_SIZE ; 
 scalar_t__ __get_free_pages (int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  bch_btree_keys_free (struct btree_keys*) ; 
 scalar_t__ bset_prev_bytes (struct btree_keys*) ; 
 scalar_t__ bset_tree_bytes (struct btree_keys*) ; 
 unsigned int get_order (scalar_t__) ; 
 void* kmalloc (scalar_t__,int /*<<< orphan*/ ) ; 

int bch_btree_keys_alloc(struct btree_keys *b,
			 unsigned int page_order,
			 gfp_t gfp)
{
	struct bset_tree *t = b->set;

	BUG_ON(t->data);

	b->page_order = page_order;

	t->data = (void *) __get_free_pages(gfp, b->page_order);
	if (!t->data)
		goto err;

	t->tree = bset_tree_bytes(b) < PAGE_SIZE
		? kmalloc(bset_tree_bytes(b), gfp)
		: (void *) __get_free_pages(gfp, get_order(bset_tree_bytes(b)));
	if (!t->tree)
		goto err;

	t->prev = bset_prev_bytes(b) < PAGE_SIZE
		? kmalloc(bset_prev_bytes(b), gfp)
		: (void *) __get_free_pages(gfp, get_order(bset_prev_bytes(b)));
	if (!t->prev)
		goto err;

	return 0;
err:
	bch_btree_keys_free(b);
	return -ENOMEM;
}