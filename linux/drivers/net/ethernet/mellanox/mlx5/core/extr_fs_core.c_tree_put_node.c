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
struct fs_node {int /*<<< orphan*/  (* del_sw_func ) (struct fs_node*) ;int /*<<< orphan*/  list; int /*<<< orphan*/  (* del_hw_func ) (struct fs_node*) ;int /*<<< orphan*/  refcount; struct fs_node* parent; } ;

/* Variables and functions */
 int /*<<< orphan*/  down_write_ref_node (struct fs_node*,int) ; 
 int /*<<< orphan*/  kfree (struct fs_node*) ; 
 int /*<<< orphan*/  list_del_init (int /*<<< orphan*/ *) ; 
 scalar_t__ refcount_dec_and_test (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct fs_node*) ; 
 int /*<<< orphan*/  stub2 (struct fs_node*) ; 
 int /*<<< orphan*/  up_write_ref_node (struct fs_node*,int) ; 

__attribute__((used)) static void tree_put_node(struct fs_node *node, bool locked)
{
	struct fs_node *parent_node = node->parent;

	if (refcount_dec_and_test(&node->refcount)) {
		if (node->del_hw_func)
			node->del_hw_func(node);
		if (parent_node) {
			/* Only root namespace doesn't have parent and we just
			 * need to free its node.
			 */
			down_write_ref_node(parent_node, locked);
			list_del_init(&node->list);
			if (node->del_sw_func)
				node->del_sw_func(node);
			up_write_ref_node(parent_node, locked);
		} else {
			kfree(node);
		}
		node = NULL;
	}
	if (!node && parent_node)
		tree_put_node(parent_node, locked);
}