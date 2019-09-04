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
struct usnic_uiom_interval_node {int /*<<< orphan*/  link; } ;
struct rb_root_cached {int dummy; } ;
struct list_head {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_LIST_HEAD (struct list_head*) ; 
 int /*<<< orphan*/  interval_cmp ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,struct list_head*) ; 
 int /*<<< orphan*/  list_sort (int /*<<< orphan*/ *,struct list_head*,int /*<<< orphan*/ ) ; 
 struct usnic_uiom_interval_node* usnic_uiom_interval_tree_iter_first (struct rb_root_cached*,unsigned long,unsigned long) ; 
 struct usnic_uiom_interval_node* usnic_uiom_interval_tree_iter_next (struct usnic_uiom_interval_node*,unsigned long,unsigned long) ; 

__attribute__((used)) static void
find_intervals_intersection_sorted(struct rb_root_cached *root,
				   unsigned long start, unsigned long last,
				   struct list_head *list)
{
	struct usnic_uiom_interval_node *node;

	INIT_LIST_HEAD(list);

	for (node = usnic_uiom_interval_tree_iter_first(root, start, last);
		node;
		node = usnic_uiom_interval_tree_iter_next(node, start, last))
		list_add_tail(&node->link, list);

	list_sort(NULL, list, interval_cmp);
}