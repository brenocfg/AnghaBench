#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int port; } ;
struct TYPE_7__ {int /*<<< orphan*/  flags; } ;
struct TYPE_8__ {TYPE_1__ parallel; } ;
struct v4l2_fwnode_endpoint {scalar_t__ bus_type; TYPE_3__ base; TYPE_2__ bus; } ;
struct fimc_source_info {int mux_id; int /*<<< orphan*/  sensor_bus_type; int /*<<< orphan*/  fimc_bus_type; int /*<<< orphan*/  flags; } ;
struct fimc_md {int /*<<< orphan*/  num_sensors; TYPE_6__* sensor; int /*<<< orphan*/  subdev_notifier; int /*<<< orphan*/  v4l2_dev; } ;
struct device_node {int dummy; } ;
struct TYPE_10__ {int /*<<< orphan*/  fwnode; } ;
struct TYPE_11__ {TYPE_4__ match; int /*<<< orphan*/  match_type; } ;
struct TYPE_12__ {TYPE_5__ asd; struct fimc_source_info pdata; } ;

/* Variables and functions */
 unsigned int ARRAY_SIZE (TYPE_6__*) ; 
 int EINVAL ; 
 int /*<<< orphan*/  FIMC_BUS_TYPE_ISP_WRITEBACK ; 
 int /*<<< orphan*/  FIMC_BUS_TYPE_ITU_601 ; 
 int /*<<< orphan*/  FIMC_BUS_TYPE_ITU_656 ; 
 int /*<<< orphan*/  FIMC_BUS_TYPE_MIPI_CSI2 ; 
 unsigned int FIMC_MAX_SENSORS ; 
 int /*<<< orphan*/  V4L2_ASYNC_MATCH_FWNODE ; 
 scalar_t__ V4L2_MBUS_PARALLEL ; 
 scalar_t__ WARN_ON (int) ; 
 scalar_t__ fimc_input_is_mipi_csi (int) ; 
 scalar_t__ fimc_input_is_parallel (int) ; 
 int /*<<< orphan*/  of_fwnode_handle (struct device_node*) ; 
 struct device_node* of_get_next_child (struct device_node*,int /*<<< orphan*/ *) ; 
 struct device_node* of_get_parent (struct device_node*) ; 
 struct device_node* of_graph_get_remote_port_parent (struct device_node*) ; 
 scalar_t__ of_node_name_eq (struct device_node*,char*) ; 
 int /*<<< orphan*/  of_node_put (struct device_node*) ; 
 int v4l2_async_notifier_add_subdev (int /*<<< orphan*/ *,TYPE_5__*) ; 
 int /*<<< orphan*/  v4l2_err (int /*<<< orphan*/ *,char*,int,struct device_node*) ; 
 int v4l2_fwnode_endpoint_parse (int /*<<< orphan*/ ,struct v4l2_fwnode_endpoint*) ; 
 int /*<<< orphan*/  v4l2_info (int /*<<< orphan*/ *,char*,struct device_node*) ; 

__attribute__((used)) static int fimc_md_parse_port_node(struct fimc_md *fmd,
				   struct device_node *port,
				   unsigned int index)
{
	struct fimc_source_info *pd = &fmd->sensor[index].pdata;
	struct device_node *rem, *ep, *np;
	struct v4l2_fwnode_endpoint endpoint = { .bus_type = 0 };
	int ret;

	/* Assume here a port node can have only one endpoint node. */
	ep = of_get_next_child(port, NULL);
	if (!ep)
		return 0;

	ret = v4l2_fwnode_endpoint_parse(of_fwnode_handle(ep), &endpoint);
	if (ret) {
		of_node_put(ep);
		return ret;
	}

	if (WARN_ON(endpoint.base.port == 0) || index >= FIMC_MAX_SENSORS) {
		of_node_put(ep);
		return -EINVAL;
	}

	pd->mux_id = (endpoint.base.port - 1) & 0x1;

	rem = of_graph_get_remote_port_parent(ep);
	of_node_put(ep);
	if (rem == NULL) {
		v4l2_info(&fmd->v4l2_dev, "Remote device at %pOF not found\n",
							ep);
		return 0;
	}

	if (fimc_input_is_parallel(endpoint.base.port)) {
		if (endpoint.bus_type == V4L2_MBUS_PARALLEL)
			pd->sensor_bus_type = FIMC_BUS_TYPE_ITU_601;
		else
			pd->sensor_bus_type = FIMC_BUS_TYPE_ITU_656;
		pd->flags = endpoint.bus.parallel.flags;
	} else if (fimc_input_is_mipi_csi(endpoint.base.port)) {
		/*
		 * MIPI CSI-2: only input mux selection and
		 * the sensor's clock frequency is needed.
		 */
		pd->sensor_bus_type = FIMC_BUS_TYPE_MIPI_CSI2;
	} else {
		v4l2_err(&fmd->v4l2_dev, "Wrong port id (%u) at node %pOF\n",
			 endpoint.base.port, rem);
	}
	/*
	 * For FIMC-IS handled sensors, that are placed under i2c-isp device
	 * node, FIMC is connected to the FIMC-IS through its ISP Writeback
	 * input. Sensors are attached to the FIMC-LITE hostdata interface
	 * directly or through MIPI-CSIS, depending on the external media bus
	 * used. This needs to be handled in a more reliable way, not by just
	 * checking parent's node name.
	 */
	np = of_get_parent(rem);

	if (of_node_name_eq(np, "i2c-isp"))
		pd->fimc_bus_type = FIMC_BUS_TYPE_ISP_WRITEBACK;
	else
		pd->fimc_bus_type = pd->sensor_bus_type;
	of_node_put(np);

	if (WARN_ON(index >= ARRAY_SIZE(fmd->sensor))) {
		of_node_put(rem);
		return -EINVAL;
	}

	fmd->sensor[index].asd.match_type = V4L2_ASYNC_MATCH_FWNODE;
	fmd->sensor[index].asd.match.fwnode = of_fwnode_handle(rem);

	ret = v4l2_async_notifier_add_subdev(&fmd->subdev_notifier,
					     &fmd->sensor[index].asd);
	if (ret) {
		of_node_put(rem);
		return ret;
	}

	fmd->num_sensors++;

	return 0;
}