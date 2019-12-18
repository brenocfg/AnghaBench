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
struct fwnode_handle {int dummy; } ;
struct device_node {int dummy; } ;

/* Variables and functions */
 struct fwnode_handle* of_fwnode_handle (struct device_node*) ; 
 struct device_node* of_get_next_parent (struct device_node*) ; 
 struct device_node* of_get_parent (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  of_node_name_eq (struct device_node*,char*) ; 
 int /*<<< orphan*/  to_of_node (struct fwnode_handle*) ; 

__attribute__((used)) static struct fwnode_handle *
of_fwnode_graph_get_port_parent(struct fwnode_handle *fwnode)
{
	struct device_node *np;

	/* Get the parent of the port */
	np = of_get_parent(to_of_node(fwnode));
	if (!np)
		return NULL;

	/* Is this the "ports" node? If not, it's the port parent. */
	if (!of_node_name_eq(np, "ports"))
		return of_fwnode_handle(np);

	return of_fwnode_handle(of_get_next_parent(np));
}