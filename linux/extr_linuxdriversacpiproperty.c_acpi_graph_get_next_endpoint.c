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
typedef  struct fwnode_handle const fwnode_handle ;

/* Variables and functions */
 struct fwnode_handle const* fwnode_get_next_child_node (struct fwnode_handle const*,struct fwnode_handle const*) ; 
 struct fwnode_handle const* fwnode_get_parent (struct fwnode_handle const*) ; 
 scalar_t__ is_acpi_graph_node (struct fwnode_handle const*,char*) ; 

__attribute__((used)) static struct fwnode_handle *acpi_graph_get_next_endpoint(
	const struct fwnode_handle *fwnode, struct fwnode_handle *prev)
{
	struct fwnode_handle *port = NULL;
	struct fwnode_handle *endpoint;

	if (!prev) {
		do {
			port = fwnode_get_next_child_node(fwnode, port);
			/*
			 * The names of the port nodes begin with "port@"
			 * followed by the number of the port node and they also
			 * have a "reg" property that also has the number of the
			 * port node. For compatibility reasons a node is also
			 * recognised as a port node from the "port" property.
			 */
			if (is_acpi_graph_node(port, "port"))
				break;
		} while (port);
	} else {
		port = fwnode_get_parent(prev);
	}

	if (!port)
		return NULL;

	endpoint = fwnode_get_next_child_node(port, prev);
	while (!endpoint) {
		port = fwnode_get_next_child_node(fwnode, port);
		if (!port)
			break;
		if (is_acpi_graph_node(port, "port"))
			endpoint = fwnode_get_next_child_node(port, NULL);
	}

	/*
	 * The names of the endpoint nodes begin with "endpoint@" followed by
	 * the number of the endpoint node and they also have a "reg" property
	 * that also has the number of the endpoint node. For compatibility
	 * reasons a node is also recognised as an endpoint node from the
	 * "endpoint" property.
	 */
	if (!is_acpi_graph_node(endpoint, "endpoint"))
		return NULL;

	return endpoint;
}