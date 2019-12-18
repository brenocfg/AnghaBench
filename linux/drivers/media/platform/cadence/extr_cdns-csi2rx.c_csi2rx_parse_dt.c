#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_9__ ;
typedef  struct TYPE_14__   TYPE_8__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {scalar_t__ num_data_lanes; int /*<<< orphan*/  data_lanes; } ;
struct TYPE_11__ {TYPE_1__ mipi_csi2; } ;
struct v4l2_fwnode_endpoint {scalar_t__ bus_type; TYPE_2__ bus; } ;
struct fwnode_handle {int dummy; } ;
struct device_node {int dummy; } ;
struct TYPE_13__ {int /*<<< orphan*/ * ops; } ;
struct TYPE_12__ {int /*<<< orphan*/  fwnode; } ;
struct TYPE_14__ {TYPE_3__ match; int /*<<< orphan*/  match_type; } ;
struct csi2rx_priv {scalar_t__ num_lanes; scalar_t__ max_lanes; TYPE_4__ notifier; int /*<<< orphan*/  subdev; TYPE_8__ asd; TYPE_9__* dev; int /*<<< orphan*/  lanes; } ;
struct TYPE_15__ {int /*<<< orphan*/  of_node; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  V4L2_ASYNC_MATCH_FWNODE ; 
 scalar_t__ V4L2_MBUS_CSI2_DPHY ; 
 int /*<<< orphan*/  csi2rx_notifier_ops ; 
 int /*<<< orphan*/  dev_err (TYPE_9__*,char*,...) ; 
 int /*<<< orphan*/  fwnode_graph_get_remote_port_parent (struct fwnode_handle*) ; 
 int /*<<< orphan*/  fwnode_handle_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 struct fwnode_handle* of_fwnode_handle (struct device_node*) ; 
 struct device_node* of_graph_get_endpoint_by_regs (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  of_node_put (struct device_node*) ; 
 int v4l2_async_notifier_add_subdev (TYPE_4__*,TYPE_8__*) ; 
 int /*<<< orphan*/  v4l2_async_notifier_cleanup (TYPE_4__*) ; 
 int /*<<< orphan*/  v4l2_async_notifier_init (TYPE_4__*) ; 
 int v4l2_async_subdev_notifier_register (int /*<<< orphan*/ *,TYPE_4__*) ; 
 int v4l2_fwnode_endpoint_parse (struct fwnode_handle*,struct v4l2_fwnode_endpoint*) ; 

__attribute__((used)) static int csi2rx_parse_dt(struct csi2rx_priv *csi2rx)
{
	struct v4l2_fwnode_endpoint v4l2_ep = { .bus_type = 0 };
	struct fwnode_handle *fwh;
	struct device_node *ep;
	int ret;

	ep = of_graph_get_endpoint_by_regs(csi2rx->dev->of_node, 0, 0);
	if (!ep)
		return -EINVAL;

	fwh = of_fwnode_handle(ep);
	ret = v4l2_fwnode_endpoint_parse(fwh, &v4l2_ep);
	if (ret) {
		dev_err(csi2rx->dev, "Could not parse v4l2 endpoint\n");
		of_node_put(ep);
		return ret;
	}

	if (v4l2_ep.bus_type != V4L2_MBUS_CSI2_DPHY) {
		dev_err(csi2rx->dev, "Unsupported media bus type: 0x%x\n",
			v4l2_ep.bus_type);
		of_node_put(ep);
		return -EINVAL;
	}

	memcpy(csi2rx->lanes, v4l2_ep.bus.mipi_csi2.data_lanes,
	       sizeof(csi2rx->lanes));
	csi2rx->num_lanes = v4l2_ep.bus.mipi_csi2.num_data_lanes;
	if (csi2rx->num_lanes > csi2rx->max_lanes) {
		dev_err(csi2rx->dev, "Unsupported number of data-lanes: %d\n",
			csi2rx->num_lanes);
		of_node_put(ep);
		return -EINVAL;
	}

	csi2rx->asd.match.fwnode = fwnode_graph_get_remote_port_parent(fwh);
	csi2rx->asd.match_type = V4L2_ASYNC_MATCH_FWNODE;
	of_node_put(ep);

	v4l2_async_notifier_init(&csi2rx->notifier);

	ret = v4l2_async_notifier_add_subdev(&csi2rx->notifier, &csi2rx->asd);
	if (ret) {
		fwnode_handle_put(csi2rx->asd.match.fwnode);
		return ret;
	}

	csi2rx->notifier.ops = &csi2rx_notifier_ops;

	ret = v4l2_async_subdev_notifier_register(&csi2rx->subdev,
						  &csi2rx->notifier);
	if (ret)
		v4l2_async_notifier_cleanup(&csi2rx->notifier);

	return ret;
}