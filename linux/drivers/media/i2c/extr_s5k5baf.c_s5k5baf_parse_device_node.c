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
struct TYPE_3__ {int /*<<< orphan*/  num_data_lanes; } ;
struct TYPE_4__ {TYPE_1__ mipi_csi2; } ;
struct v4l2_fwnode_endpoint {TYPE_2__ bus; int /*<<< orphan*/  bus_type; } ;
struct s5k5baf {int /*<<< orphan*/  nlanes; int /*<<< orphan*/  bus_type; int /*<<< orphan*/  gpios; int /*<<< orphan*/  mclk_frequency; } ;
struct device_node {int dummy; } ;
struct device {struct device_node* of_node; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  S5K5BAF_DEFAULT_MCLK_FREQ ; 
#define  V4L2_MBUS_CSI2_DPHY 129 
#define  V4L2_MBUS_PARALLEL 128 
 int /*<<< orphan*/  dev_err (struct device*,char*,...) ; 
 int /*<<< orphan*/  dev_info (struct device*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  of_fwnode_handle (struct device_node*) ; 
 struct device_node* of_graph_get_next_endpoint (struct device_node*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  of_node_put (struct device_node*) ; 
 int of_property_read_u32 (struct device_node*,char*,int /*<<< orphan*/ *) ; 
 int s5k5baf_parse_gpios (int /*<<< orphan*/ ,struct device*) ; 
 int v4l2_fwnode_endpoint_parse (int /*<<< orphan*/ ,struct v4l2_fwnode_endpoint*) ; 

__attribute__((used)) static int s5k5baf_parse_device_node(struct s5k5baf *state, struct device *dev)
{
	struct device_node *node = dev->of_node;
	struct device_node *node_ep;
	struct v4l2_fwnode_endpoint ep = { .bus_type = 0 };
	int ret;

	if (!node) {
		dev_err(dev, "no device-tree node provided\n");
		return -EINVAL;
	}

	ret = of_property_read_u32(node, "clock-frequency",
				   &state->mclk_frequency);
	if (ret < 0) {
		state->mclk_frequency = S5K5BAF_DEFAULT_MCLK_FREQ;
		dev_info(dev, "using default %u Hz clock frequency\n",
			 state->mclk_frequency);
	}

	ret = s5k5baf_parse_gpios(state->gpios, dev);
	if (ret < 0)
		return ret;

	node_ep = of_graph_get_next_endpoint(node, NULL);
	if (!node_ep) {
		dev_err(dev, "no endpoint defined at node %pOF\n", node);
		return -EINVAL;
	}

	ret = v4l2_fwnode_endpoint_parse(of_fwnode_handle(node_ep), &ep);
	of_node_put(node_ep);
	if (ret)
		return ret;

	state->bus_type = ep.bus_type;

	switch (state->bus_type) {
	case V4L2_MBUS_CSI2_DPHY:
		state->nlanes = ep.bus.mipi_csi2.num_data_lanes;
		break;
	case V4L2_MBUS_PARALLEL:
		break;
	default:
		dev_err(dev, "unsupported bus in endpoint defined at node %pOF\n",
			node);
		return -EINVAL;
	}

	return 0;
}