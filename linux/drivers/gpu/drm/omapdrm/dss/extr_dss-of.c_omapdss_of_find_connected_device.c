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
 int /*<<< orphan*/  EPROBE_DEFER ; 
 struct omap_dss_device* ERR_PTR (int /*<<< orphan*/ ) ; 
 struct device_node* of_graph_get_remote_node (struct device_node*,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  of_node_put (struct device_node*) ; 
 struct omap_dss_device* omapdss_find_device_by_node (struct device_node*) ; 

struct omap_dss_device *
omapdss_of_find_connected_device(struct device_node *node, unsigned int port)
{
	struct device_node *remote_node;
	struct omap_dss_device *dssdev;

	remote_node = of_graph_get_remote_node(node, port, 0);
	if (!remote_node)
		return NULL;

	dssdev = omapdss_find_device_by_node(remote_node);
	of_node_put(remote_node);

	return dssdev ? dssdev : ERR_PTR(-EPROBE_DEFER);
}