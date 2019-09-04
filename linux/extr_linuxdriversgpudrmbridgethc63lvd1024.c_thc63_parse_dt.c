#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct thc63_dev {int /*<<< orphan*/  next; TYPE_1__* dev; } ;
struct device_node {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  of_node; } ;

/* Variables and functions */
 int ENODEV ; 
 int EPROBE_DEFER ; 
 int /*<<< orphan*/  THC63_RGB_OUT0 ; 
 int /*<<< orphan*/  dev_err (TYPE_1__*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  of_device_is_available (struct device_node*) ; 
 int /*<<< orphan*/  of_drm_find_bridge (struct device_node*) ; 
 struct device_node* of_graph_get_endpoint_by_regs (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 struct device_node* of_graph_get_remote_port_parent (struct device_node*) ; 
 int /*<<< orphan*/  of_node_put (struct device_node*) ; 

__attribute__((used)) static int thc63_parse_dt(struct thc63_dev *thc63)
{
	struct device_node *thc63_out;
	struct device_node *remote;

	thc63_out = of_graph_get_endpoint_by_regs(thc63->dev->of_node,
						  THC63_RGB_OUT0, -1);
	if (!thc63_out) {
		dev_err(thc63->dev, "Missing endpoint in port@%u\n",
			THC63_RGB_OUT0);
		return -ENODEV;
	}

	remote = of_graph_get_remote_port_parent(thc63_out);
	of_node_put(thc63_out);
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

	return 0;
}