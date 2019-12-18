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
 struct device_node* of_node_get (struct device_node*) ; 
 int /*<<< orphan*/  of_node_put (struct device_node*) ; 
 scalar_t__ of_property_read_bool (struct device_node*,char*) ; 

bool of_dma_is_coherent(struct device_node *np)
{
	struct device_node *node = of_node_get(np);

	while (node) {
		if (of_property_read_bool(node, "dma-coherent")) {
			of_node_put(node);
			return true;
		}
		node = of_get_next_parent(node);
	}
	of_node_put(node);
	return false;
}