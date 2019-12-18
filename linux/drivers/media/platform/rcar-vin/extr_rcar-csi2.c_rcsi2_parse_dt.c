#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_7__ ;
typedef  struct TYPE_11__   TYPE_6__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct v4l2_fwnode_endpoint {int /*<<< orphan*/  bus_type; } ;
struct TYPE_10__ {int /*<<< orphan*/ * ops; } ;
struct TYPE_9__ {int /*<<< orphan*/  fwnode; } ;
struct TYPE_11__ {TYPE_1__ match; int /*<<< orphan*/  match_type; } ;
struct rcar_csi2 {TYPE_2__ notifier; int /*<<< orphan*/  subdev; TYPE_6__ asd; TYPE_7__* dev; } ;
struct device_node {int dummy; } ;
struct TYPE_12__ {int /*<<< orphan*/  of_node; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  V4L2_ASYNC_MATCH_FWNODE ; 
 int /*<<< orphan*/  dev_dbg (TYPE_7__*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (TYPE_7__*,char*) ; 
 int /*<<< orphan*/  fwnode_graph_get_remote_endpoint (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fwnode_handle_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  of_fwnode_handle (struct device_node*) ; 
 struct device_node* of_graph_get_endpoint_by_regs (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  of_node_put (struct device_node*) ; 
 int /*<<< orphan*/  rcar_csi2_notify_ops ; 
 int rcsi2_parse_v4l2 (struct rcar_csi2*,struct v4l2_fwnode_endpoint*) ; 
 int /*<<< orphan*/  to_of_node (int /*<<< orphan*/ ) ; 
 int v4l2_async_notifier_add_subdev (TYPE_2__*,TYPE_6__*) ; 
 int /*<<< orphan*/  v4l2_async_notifier_cleanup (TYPE_2__*) ; 
 int /*<<< orphan*/  v4l2_async_notifier_init (TYPE_2__*) ; 
 int v4l2_async_subdev_notifier_register (int /*<<< orphan*/ *,TYPE_2__*) ; 
 int v4l2_fwnode_endpoint_parse (int /*<<< orphan*/ ,struct v4l2_fwnode_endpoint*) ; 

__attribute__((used)) static int rcsi2_parse_dt(struct rcar_csi2 *priv)
{
	struct device_node *ep;
	struct v4l2_fwnode_endpoint v4l2_ep = { .bus_type = 0 };
	int ret;

	ep = of_graph_get_endpoint_by_regs(priv->dev->of_node, 0, 0);
	if (!ep) {
		dev_err(priv->dev, "Not connected to subdevice\n");
		return -EINVAL;
	}

	ret = v4l2_fwnode_endpoint_parse(of_fwnode_handle(ep), &v4l2_ep);
	if (ret) {
		dev_err(priv->dev, "Could not parse v4l2 endpoint\n");
		of_node_put(ep);
		return -EINVAL;
	}

	ret = rcsi2_parse_v4l2(priv, &v4l2_ep);
	if (ret) {
		of_node_put(ep);
		return ret;
	}

	priv->asd.match.fwnode =
		fwnode_graph_get_remote_endpoint(of_fwnode_handle(ep));
	priv->asd.match_type = V4L2_ASYNC_MATCH_FWNODE;

	of_node_put(ep);

	v4l2_async_notifier_init(&priv->notifier);

	ret = v4l2_async_notifier_add_subdev(&priv->notifier, &priv->asd);
	if (ret) {
		fwnode_handle_put(priv->asd.match.fwnode);
		return ret;
	}

	priv->notifier.ops = &rcar_csi2_notify_ops;

	dev_dbg(priv->dev, "Found '%pOF'\n",
		to_of_node(priv->asd.match.fwnode));

	ret = v4l2_async_subdev_notifier_register(&priv->subdev,
						  &priv->notifier);
	if (ret)
		v4l2_async_notifier_cleanup(&priv->notifier);

	return ret;
}