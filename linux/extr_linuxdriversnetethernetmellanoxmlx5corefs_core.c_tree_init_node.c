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
struct fs_node {void (* del_hw_func ) (struct fs_node*) ;void (* del_sw_func ) (struct fs_node*) ;int active; int /*<<< orphan*/  lock; int /*<<< orphan*/  children; int /*<<< orphan*/  list; int /*<<< orphan*/  refcount; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  init_rwsem (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  refcount_set (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void tree_init_node(struct fs_node *node,
			   void (*del_hw_func)(struct fs_node *),
			   void (*del_sw_func)(struct fs_node *))
{
	refcount_set(&node->refcount, 1);
	INIT_LIST_HEAD(&node->list);
	INIT_LIST_HEAD(&node->children);
	init_rwsem(&node->lock);
	node->del_hw_func = del_hw_func;
	node->del_sw_func = del_sw_func;
	node->active = false;
}