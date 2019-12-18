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
struct of_endpoint {int id; } ;
struct device_node {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 struct device_node* of_graph_get_endpoint_by_regs (struct device_node*,int,int) ; 
 struct device_node* of_graph_get_remote_endpoint (struct device_node*) ; 
 int /*<<< orphan*/  of_graph_parse_endpoint (struct device_node*,struct of_endpoint*) ; 
 int /*<<< orphan*/  of_node_put (struct device_node*) ; 

__attribute__((used)) static int sun8i_mixer_of_get_id(struct device_node *node)
{
	struct device_node *ep, *remote;
	struct of_endpoint of_ep;

	/* Output port is 1, and we want the first endpoint. */
	ep = of_graph_get_endpoint_by_regs(node, 1, -1);
	if (!ep)
		return -EINVAL;

	remote = of_graph_get_remote_endpoint(ep);
	of_node_put(ep);
	if (!remote)
		return -EINVAL;

	of_graph_parse_endpoint(remote, &of_ep);
	of_node_put(remote);
	return of_ep.id;
}