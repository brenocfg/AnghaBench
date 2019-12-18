#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_7__ ;
typedef  struct TYPE_16__   TYPE_6__ ;
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_15__ {int num_data_lanes; int /*<<< orphan*/ * data_lanes; int /*<<< orphan*/  clock_lane; int /*<<< orphan*/  flags; } ;
struct TYPE_16__ {TYPE_5__ mipi_csi2; } ;
struct TYPE_14__ {int /*<<< orphan*/  id; } ;
struct v4l2_fwnode_endpoint {scalar_t__ bus_type; TYPE_6__ bus; TYPE_4__ base; } ;
struct TYPE_13__ {int /*<<< orphan*/  fwnode; } ;
struct v4l2_async_subdev {TYPE_3__ match; int /*<<< orphan*/  match_type; } ;
struct TYPE_12__ {struct device_node* of_node; } ;
struct platform_device {TYPE_2__ dev; } ;
struct device_node {int dummy; } ;
struct TYPE_17__ {int /*<<< orphan*/ * ops; } ;
struct cal_ctx {TYPE_7__ notifier; int /*<<< orphan*/  v4l2_dev; int /*<<< orphan*/  virtual_channel; struct v4l2_fwnode_endpoint endpoint; struct v4l2_async_subdev asd; TYPE_1__* dev; } ;
struct TYPE_11__ {struct platform_device* pdev; } ;

/* Variables and functions */
 int CAL_NUM_CSI2_PORTS ; 
 int EINVAL ; 
 int /*<<< orphan*/  V4L2_ASYNC_MATCH_FWNODE ; 
 scalar_t__ V4L2_MBUS_CSI2_DPHY ; 
 int /*<<< orphan*/  cal_async_ops ; 
 int /*<<< orphan*/  ctx_dbg (int,struct cal_ctx*,char*,...) ; 
 int /*<<< orphan*/  ctx_err (struct cal_ctx*,char*,...) ; 
 int /*<<< orphan*/  of_fwnode_handle (struct device_node*) ; 
 struct device_node* of_get_next_endpoint (struct device_node*,struct device_node*) ; 
 struct device_node* of_get_next_port (struct device_node*,struct device_node*) ; 
 struct device_node* of_graph_get_remote_port_parent (struct device_node*) ; 
 int /*<<< orphan*/  of_node_put (struct device_node*) ; 
 int /*<<< orphan*/  of_property_read_u32 (struct device_node*,char*,int*) ; 
 int v4l2_async_notifier_add_subdev (TYPE_7__*,struct v4l2_async_subdev*) ; 
 int /*<<< orphan*/  v4l2_async_notifier_cleanup (TYPE_7__*) ; 
 int /*<<< orphan*/  v4l2_async_notifier_init (TYPE_7__*) ; 
 int v4l2_async_notifier_register (int /*<<< orphan*/ *,TYPE_7__*) ; 
 int /*<<< orphan*/  v4l2_fwnode_endpoint_parse (int /*<<< orphan*/ ,struct v4l2_fwnode_endpoint*) ; 

__attribute__((used)) static int of_cal_create_instance(struct cal_ctx *ctx, int inst)
{
	struct platform_device *pdev = ctx->dev->pdev;
	struct device_node *ep_node, *port, *sensor_node, *parent;
	struct v4l2_fwnode_endpoint *endpoint;
	struct v4l2_async_subdev *asd;
	u32 regval = 0;
	int ret, index, found_port = 0, lane;

	parent = pdev->dev.of_node;

	asd = &ctx->asd;
	endpoint = &ctx->endpoint;

	ep_node = NULL;
	port = NULL;
	sensor_node = NULL;
	ret = -EINVAL;

	ctx_dbg(3, ctx, "Scanning Port node for csi2 port: %d\n", inst);
	for (index = 0; index < CAL_NUM_CSI2_PORTS; index++) {
		port = of_get_next_port(parent, port);
		if (!port) {
			ctx_dbg(1, ctx, "No port node found for csi2 port:%d\n",
				index);
			goto cleanup_exit;
		}

		/* Match the slice number with <REG> */
		of_property_read_u32(port, "reg", &regval);
		ctx_dbg(3, ctx, "port:%d inst:%d <reg>:%d\n",
			index, inst, regval);
		if ((regval == inst) && (index == inst)) {
			found_port = 1;
			break;
		}
	}

	if (!found_port) {
		ctx_dbg(1, ctx, "No port node matches csi2 port:%d\n",
			inst);
		goto cleanup_exit;
	}

	ctx_dbg(3, ctx, "Scanning sub-device for csi2 port: %d\n",
		inst);

	ep_node = of_get_next_endpoint(port, ep_node);
	if (!ep_node) {
		ctx_dbg(3, ctx, "can't get next endpoint\n");
		goto cleanup_exit;
	}

	sensor_node = of_graph_get_remote_port_parent(ep_node);
	if (!sensor_node) {
		ctx_dbg(3, ctx, "can't get remote parent\n");
		goto cleanup_exit;
	}
	asd->match_type = V4L2_ASYNC_MATCH_FWNODE;
	asd->match.fwnode = of_fwnode_handle(sensor_node);

	v4l2_fwnode_endpoint_parse(of_fwnode_handle(ep_node), endpoint);

	if (endpoint->bus_type != V4L2_MBUS_CSI2_DPHY) {
		ctx_err(ctx, "Port:%d sub-device %pOFn is not a CSI2 device\n",
			inst, sensor_node);
		goto cleanup_exit;
	}

	/* Store Virtual Channel number */
	ctx->virtual_channel = endpoint->base.id;

	ctx_dbg(3, ctx, "Port:%d v4l2-endpoint: CSI2\n", inst);
	ctx_dbg(3, ctx, "Virtual Channel=%d\n", ctx->virtual_channel);
	ctx_dbg(3, ctx, "flags=0x%08x\n", endpoint->bus.mipi_csi2.flags);
	ctx_dbg(3, ctx, "clock_lane=%d\n", endpoint->bus.mipi_csi2.clock_lane);
	ctx_dbg(3, ctx, "num_data_lanes=%d\n",
		endpoint->bus.mipi_csi2.num_data_lanes);
	ctx_dbg(3, ctx, "data_lanes= <\n");
	for (lane = 0; lane < endpoint->bus.mipi_csi2.num_data_lanes; lane++)
		ctx_dbg(3, ctx, "\t%d\n",
			endpoint->bus.mipi_csi2.data_lanes[lane]);
	ctx_dbg(3, ctx, "\t>\n");

	ctx_dbg(1, ctx, "Port: %d found sub-device %pOFn\n",
		inst, sensor_node);

	v4l2_async_notifier_init(&ctx->notifier);

	ret = v4l2_async_notifier_add_subdev(&ctx->notifier, asd);
	if (ret) {
		ctx_err(ctx, "Error adding asd\n");
		goto cleanup_exit;
	}

	ctx->notifier.ops = &cal_async_ops;
	ret = v4l2_async_notifier_register(&ctx->v4l2_dev,
					   &ctx->notifier);
	if (ret) {
		ctx_err(ctx, "Error registering async notifier\n");
		v4l2_async_notifier_cleanup(&ctx->notifier);
		ret = -EINVAL;
	}

	/*
	 * On success we need to keep reference on sensor_node, or
	 * if notifier_cleanup was called above, sensor_node was
	 * already put.
	 */
	sensor_node = NULL;

cleanup_exit:
	of_node_put(sensor_node);
	of_node_put(ep_node);
	of_node_put(port);

	return ret;
}