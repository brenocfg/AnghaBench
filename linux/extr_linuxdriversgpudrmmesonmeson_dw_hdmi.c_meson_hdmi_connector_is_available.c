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
struct device {int /*<<< orphan*/  of_node; } ;

/* Variables and functions */
 struct device_node* of_graph_get_endpoint_by_regs (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 struct device_node* of_graph_get_remote_port (struct device_node*) ; 
 int /*<<< orphan*/  of_node_put (struct device_node*) ; 

__attribute__((used)) static bool meson_hdmi_connector_is_available(struct device *dev)
{
	struct device_node *ep, *remote;

	/* HDMI Connector is on the second port, first endpoint */
	ep = of_graph_get_endpoint_by_regs(dev->of_node, 1, 0);
	if (!ep)
		return false;

	/* If the endpoint node exists, consider it enabled */
	remote = of_graph_get_remote_port(ep);
	if (remote) {
		of_node_put(ep);
		return true;
	}

	of_node_put(ep);
	of_node_put(remote);

	return false;
}