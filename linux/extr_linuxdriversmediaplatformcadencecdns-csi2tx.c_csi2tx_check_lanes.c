#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  data_lanes; int /*<<< orphan*/  num_data_lanes; } ;
struct TYPE_5__ {TYPE_1__ mipi_csi2; } ;
struct v4l2_fwnode_endpoint {scalar_t__ bus_type; TYPE_2__ bus; } ;
struct device_node {int dummy; } ;
struct csi2tx_priv {int /*<<< orphan*/  lanes; TYPE_3__* dev; int /*<<< orphan*/  max_lanes; int /*<<< orphan*/  num_lanes; } ;
struct TYPE_6__ {int /*<<< orphan*/  of_node; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ V4L2_MBUS_CSI2 ; 
 int /*<<< orphan*/  dev_err (TYPE_3__*,char*,...) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  of_fwnode_handle (struct device_node*) ; 
 struct device_node* of_graph_get_endpoint_by_regs (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  of_node_put (struct device_node*) ; 
 int v4l2_fwnode_endpoint_parse (int /*<<< orphan*/ ,struct v4l2_fwnode_endpoint*) ; 

__attribute__((used)) static int csi2tx_check_lanes(struct csi2tx_priv *csi2tx)
{
	struct v4l2_fwnode_endpoint v4l2_ep;
	struct device_node *ep;
	int ret;

	ep = of_graph_get_endpoint_by_regs(csi2tx->dev->of_node, 0, 0);
	if (!ep)
		return -EINVAL;

	ret = v4l2_fwnode_endpoint_parse(of_fwnode_handle(ep), &v4l2_ep);
	if (ret) {
		dev_err(csi2tx->dev, "Could not parse v4l2 endpoint\n");
		goto out;
	}

	if (v4l2_ep.bus_type != V4L2_MBUS_CSI2) {
		dev_err(csi2tx->dev, "Unsupported media bus type: 0x%x\n",
			v4l2_ep.bus_type);
		ret = -EINVAL;
		goto out;
	}

	csi2tx->num_lanes = v4l2_ep.bus.mipi_csi2.num_data_lanes;
	if (csi2tx->num_lanes > csi2tx->max_lanes) {
		dev_err(csi2tx->dev,
			"Current configuration uses more lanes than supported\n");
		ret = -EINVAL;
		goto out;
	}

	memcpy(csi2tx->lanes, v4l2_ep.bus.mipi_csi2.data_lanes,
	       sizeof(csi2tx->lanes));

out:
	of_node_put(ep);
	return ret;
}