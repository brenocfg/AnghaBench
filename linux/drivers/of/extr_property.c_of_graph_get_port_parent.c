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
struct device_node {int dummy; } ;

/* Variables and functions */
 struct device_node* of_get_next_parent (struct device_node*) ; 
 int /*<<< orphan*/  of_node_get (struct device_node*) ; 
 int /*<<< orphan*/  of_node_name_eq (struct device_node*,char*) ; 

struct device_node *of_graph_get_port_parent(struct device_node *node)
{
	unsigned int depth;

	if (!node)
		return NULL;

	/*
	 * Preserve usecount for passed in node as of_get_next_parent()
	 * will do of_node_put() on it.
	 */
	of_node_get(node);

	/* Walk 3 levels up only if there is 'ports' node. */
	for (depth = 3; depth && node; depth--) {
		node = of_get_next_parent(node);
		if (depth == 2 && !of_node_name_eq(node, "ports"))
			break;
	}
	return node;
}