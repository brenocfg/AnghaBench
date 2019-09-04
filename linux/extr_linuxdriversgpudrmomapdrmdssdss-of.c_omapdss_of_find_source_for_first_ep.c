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
struct omap_dss_device {int dummy; } ;
struct device_node {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  EPROBE_DEFER ; 
 struct omap_dss_device* ERR_PTR (int /*<<< orphan*/ ) ; 
 struct device_node* of_graph_get_endpoint_by_regs (struct device_node*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct device_node* of_graph_get_remote_port (struct device_node*) ; 
 int /*<<< orphan*/  of_node_put (struct device_node*) ; 
 struct omap_dss_device* omap_dss_find_output_by_port_node (struct device_node*) ; 

struct omap_dss_device *
omapdss_of_find_source_for_first_ep(struct device_node *node)
{
	struct device_node *ep;
	struct device_node *src_port;
	struct omap_dss_device *src;

	ep = of_graph_get_endpoint_by_regs(node, 0, 0);
	if (!ep)
		return ERR_PTR(-EINVAL);

	src_port = of_graph_get_remote_port(ep);
	if (!src_port) {
		of_node_put(ep);
		return ERR_PTR(-EINVAL);
	}

	of_node_put(ep);

	src = omap_dss_find_output_by_port_node(src_port);

	of_node_put(src_port);

	return src ? src : ERR_PTR(-EPROBE_DEFER);
}