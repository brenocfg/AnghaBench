#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int dual_link; } ;
struct thc63_dev {TYPE_1__ timings; TYPE_2__* dev; int /*<<< orphan*/  next; } ;
struct device_node {int dummy; } ;
struct TYPE_5__ {int /*<<< orphan*/  of_node; } ;

/* Variables and functions */
 int ENODEV ; 
 int EPROBE_DEFER ; 
 int /*<<< orphan*/  THC63_LVDS_IN1 ; 
 int /*<<< orphan*/  THC63_RGB_OUT0 ; 
 int /*<<< orphan*/  dev_dbg (TYPE_2__*,char*,char*) ; 
 int /*<<< orphan*/  dev_err (TYPE_2__*,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ of_device_is_available (struct device_node*) ; 
 int /*<<< orphan*/  of_drm_find_bridge (struct device_node*) ; 
 struct device_node* of_graph_get_endpoint_by_regs (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 struct device_node* of_graph_get_remote_port_parent (struct device_node*) ; 
 int /*<<< orphan*/  of_node_put (struct device_node*) ; 

__attribute__((used)) static int thc63_parse_dt(struct thc63_dev *thc63)
{
	struct device_node *endpoint;
	struct device_node *remote;

	endpoint = of_graph_get_endpoint_by_regs(thc63->dev->of_node,
						 THC63_RGB_OUT0, -1);
	if (!endpoint) {
		dev_err(thc63->dev, "Missing endpoint in port@%u\n",
			THC63_RGB_OUT0);
		return -ENODEV;
	}

	remote = of_graph_get_remote_port_parent(endpoint);
	of_node_put(endpoint);
	if (!remote) {
		dev_err(thc63->dev, "Endpoint in port@%u unconnected\n",
			THC63_RGB_OUT0);
		return -ENODEV;
	}

	if (!of_device_is_available(remote)) {
		dev_err(thc63->dev, "port@%u remote endpoint is disabled\n",
			THC63_RGB_OUT0);
		of_node_put(remote);
		return -ENODEV;
	}

	thc63->next = of_drm_find_bridge(remote);
	of_node_put(remote);
	if (!thc63->next)
		return -EPROBE_DEFER;

	endpoint = of_graph_get_endpoint_by_regs(thc63->dev->of_node,
						 THC63_LVDS_IN1, -1);
	if (endpoint) {
		remote = of_graph_get_remote_port_parent(endpoint);
		of_node_put(endpoint);

		if (remote) {
			if (of_device_is_available(remote))
				thc63->timings.dual_link = true;
			of_node_put(remote);
		}
	}

	dev_dbg(thc63->dev, "operating in %s-link mode\n",
		thc63->timings.dual_link ? "dual" : "single");

	return 0;
}