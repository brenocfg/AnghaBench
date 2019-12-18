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
struct rb_root {int /*<<< orphan*/ * rb_node; } ;
struct rb_node {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  kfree (struct rb_node*) ; 
 int /*<<< orphan*/  rb_erase (struct rb_node*,struct rb_root*) ; 
 struct rb_node* rb_first (struct rb_root*) ; 
 struct rb_node* rb_next (struct rb_node*) ; 

__attribute__((used)) static bool __dust_clear_badblocks(struct rb_root *tree,
				   unsigned long long count)
{
	struct rb_node *node = NULL, *nnode = NULL;

	nnode = rb_first(tree);
	if (nnode == NULL) {
		BUG_ON(count != 0);
		return false;
	}

	while (nnode) {
		node = nnode;
		nnode = rb_next(node);
		rb_erase(node, tree);
		count--;
		kfree(node);
	}
	BUG_ON(count != 0);
	BUG_ON(tree->rb_node != NULL);

	return true;
}