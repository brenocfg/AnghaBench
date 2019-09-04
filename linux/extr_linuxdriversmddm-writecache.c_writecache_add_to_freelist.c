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
struct rb_node {struct rb_node* rb_right; struct rb_node* rb_left; } ;
struct wc_entry {int /*<<< orphan*/  lru; struct rb_node rb_node; } ;
struct TYPE_2__ {struct rb_node* rb_node; } ;
struct dm_writecache {int /*<<< orphan*/  freelist_size; int /*<<< orphan*/  freelist; TYPE_1__ freetree; struct wc_entry* current_free; } ;

/* Variables and functions */
 scalar_t__ WC_MODE_SORT_FREELIST (struct dm_writecache*) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rb_insert_color (struct rb_node*,TYPE_1__*) ; 
 int /*<<< orphan*/  rb_link_node (struct rb_node*,struct rb_node*,struct rb_node**) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static void writecache_add_to_freelist(struct dm_writecache *wc, struct wc_entry *e)
{
	if (WC_MODE_SORT_FREELIST(wc)) {
		struct rb_node **node = &wc->freetree.rb_node, *parent = NULL;
		if (unlikely(!*node))
			wc->current_free = e;
		while (*node) {
			parent = *node;
			if (&e->rb_node < *node)
				node = &parent->rb_left;
			else
				node = &parent->rb_right;
		}
		rb_link_node(&e->rb_node, parent, node);
		rb_insert_color(&e->rb_node, &wc->freetree);
	} else {
		list_add_tail(&e->lru, &wc->freelist);
	}
	wc->freelist_size++;
}