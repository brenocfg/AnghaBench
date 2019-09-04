#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct v4l2_fwnode_endpoint {int dummy; } ;
struct TYPE_8__ {int num_subdevs; int /*<<< orphan*/ * ops; TYPE_3__** subdevs; } ;
struct TYPE_7__ {int /*<<< orphan*/  fwnode; } ;
struct TYPE_9__ {TYPE_1__ match; int /*<<< orphan*/  match_type; } ;
struct rcar_csi2 {TYPE_2__ notifier; int /*<<< orphan*/  subdev; TYPE_3__ asd; TYPE_4__* dev; } ;
struct device_node {int dummy; } ;
struct TYPE_10__ {int /*<<< orphan*/  of_node; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  V4L2_ASYNC_MATCH_FWNODE ; 
 int /*<<< orphan*/  dev_dbg (TYPE_4__*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (TYPE_4__*,char*) ; 
 TYPE_3__** devm_kzalloc (TYPE_4__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fwnode_graph_get_remote_endpoint (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  of_fwnode_handle (struct device_node*) ; 
 struct device_node* of_graph_get_endpoint_by_regs (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  of_node_put (struct device_node*) ; 
 int /*<<< orphan*/  rcar_csi2_notify_ops ; 
 int rcsi2_parse_v4l2 (struct rcar_csi2*,struct v4l2_fwnode_endpoint*) ; 
 int /*<<< orphan*/  to_of_node (int /*<<< orphan*/ ) ; 
 int v4l2_async_subdev_notifier_register (int /*<<< orphan*/ *,TYPE_2__*) ; 
 int v4l2_fwnode_endpoint_parse (int /*<<< orphan*/ ,struct v4l2_fwnode_endpoint*) ; 

__attribute__((used)) static int rcsi2_parse_dt(struct rcar_csi2 *priv)
{
	struct device_node *ep;
	struct v4l2_fwnode_endpoint v4l2_ep;
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

	priv->notifier.subdevs = devm_kzalloc(priv->dev,
					      sizeof(*priv->notifier.subdevs),
					      GFP_KERNEL);
	if (!priv->notifier.subdevs)
		return -ENOMEM;

	priv->notifier.num_subdevs = 1;
	priv->notifier.subdevs[0] = &priv->asd;
	priv->notifier.ops = &rcar_csi2_notify_ops;

	dev_dbg(priv->dev, "Found '%pOF'\n",
		to_of_node(priv->asd.match.fwnode));

	return v4l2_async_subdev_notifier_register(&priv->subdev,
						   &priv->notifier);
}