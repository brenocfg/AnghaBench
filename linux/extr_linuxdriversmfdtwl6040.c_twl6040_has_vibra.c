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
 struct device_node* of_get_child_by_name (struct device_node*,char*) ; 
 int /*<<< orphan*/  of_node_put (struct device_node*) ; 

__attribute__((used)) static bool twl6040_has_vibra(struct device_node *parent)
{
	struct device_node *node;

	node = of_get_child_by_name(parent, "vibra");
	if (node) {
		of_node_put(node);
		return true;
	}

	return false;
}