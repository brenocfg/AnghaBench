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
 struct device_node* of_find_node_by_name (int /*<<< orphan*/ *,char*) ; 
 struct device_node* of_get_next_child (struct device_node*,struct device_node*) ; 
 int /*<<< orphan*/  of_node_put (struct device_node*) ; 
 int /*<<< orphan*/  vio_register_device_node (struct device_node*) ; 

__attribute__((used)) static void vio_bus_scan_register_devices(char *root_name)
{
	struct device_node *node_root, *node_child;

	if (!root_name)
		return;

	node_root = of_find_node_by_name(NULL, root_name);
	if (node_root) {

		/*
		 * Create struct vio_devices for each virtual device in
		 * the device tree. Drivers will associate with them later.
		 */
		node_child = of_get_next_child(node_root, NULL);
		while (node_child) {
			vio_register_device_node(node_child);
			node_child = of_get_next_child(node_root, node_child);
		}
		of_node_put(node_root);
	}
}