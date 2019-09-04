#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  flags; } ;
struct TYPE_4__ {TYPE_1__ mipi_csi2; } ;
struct v4l2_fwnode_endpoint {TYPE_2__ bus; } ;
struct ov5647 {int /*<<< orphan*/  flags; } ;
struct device_node {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  of_fwnode_handle (struct device_node*) ; 
 struct device_node* of_graph_get_next_endpoint (struct device_node*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  of_node_put (struct device_node*) ; 
 int v4l2_fwnode_endpoint_parse (int /*<<< orphan*/ ,struct v4l2_fwnode_endpoint*) ; 

__attribute__((used)) static int ov5647_parse_dt(struct device_node *np, struct ov5647 *sensor)
{
	struct v4l2_fwnode_endpoint bus_cfg;
	struct device_node *ep;

	int ret;

	ep = of_graph_get_next_endpoint(np, NULL);
	if (!ep)
		return -EINVAL;

	ret = v4l2_fwnode_endpoint_parse(of_fwnode_handle(ep), &bus_cfg);

	if (!ret)
		sensor->flags = bus_cfg.bus.mipi_csi2.flags;

	of_node_put(ep);
	return ret;
}