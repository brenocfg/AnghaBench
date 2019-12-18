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
struct device_node {struct device_node* sibling; struct device_node* child; } ;

/* Variables and functions */
 scalar_t__ __of_node_is_type (struct device_node*,char*) ; 
 int /*<<< orphan*/  devtree_lock ; 
 struct device_node* of_find_node_by_path (char*) ; 
 scalar_t__ of_node_get (struct device_node*) ; 
 scalar_t__ of_node_name_eq (struct device_node*,char*) ; 
 int /*<<< orphan*/  of_node_put (struct device_node*) ; 
 int /*<<< orphan*/  raw_spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  raw_spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

struct device_node *of_get_next_cpu_node(struct device_node *prev)
{
	struct device_node *next = NULL;
	unsigned long flags;
	struct device_node *node;

	if (!prev)
		node = of_find_node_by_path("/cpus");

	raw_spin_lock_irqsave(&devtree_lock, flags);
	if (prev)
		next = prev->sibling;
	else if (node) {
		next = node->child;
		of_node_put(node);
	}
	for (; next; next = next->sibling) {
		if (!(of_node_name_eq(next, "cpu") ||
		      __of_node_is_type(next, "cpu")))
			continue;
		if (of_node_get(next))
			break;
	}
	of_node_put(prev);
	raw_spin_unlock_irqrestore(&devtree_lock, flags);
	return next;
}