#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  num_data_lanes; } ;
struct TYPE_7__ {TYPE_2__ mipi_csi2; } ;
struct TYPE_5__ {scalar_t__ port; } ;
struct v4l2_fwnode_endpoint {TYPE_3__ bus; TYPE_1__ base; int /*<<< orphan*/  bus_type; } ;
struct TYPE_8__ {struct device_node* of_node; } ;
struct platform_device {TYPE_4__ dev; } ;
struct device_node {int dummy; } ;
struct csis_state {scalar_t__ index; int /*<<< orphan*/  num_lanes; int /*<<< orphan*/  wclk_ext; int /*<<< orphan*/  hs_settle; int /*<<< orphan*/  max_num_lanes; int /*<<< orphan*/  clk_frequency; } ;

/* Variables and functions */
 scalar_t__ CSIS_MAX_ENTITIES ; 
 int /*<<< orphan*/  DEFAULT_SCLK_CSIS_FREQ ; 
 int EINVAL ; 
 int ENXIO ; 
 scalar_t__ FIMC_INPUT_MIPI_CSI2_0 ; 
 int /*<<< orphan*/  dev_err (TYPE_4__*,char*,struct device_node*) ; 
 int /*<<< orphan*/  of_fwnode_handle (struct device_node*) ; 
 struct device_node* of_graph_get_next_endpoint (struct device_node*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  of_node_put (struct device_node*) ; 
 int /*<<< orphan*/  of_property_read_bool (struct device_node*,char*) ; 
 scalar_t__ of_property_read_u32 (struct device_node*,char*,int /*<<< orphan*/ *) ; 
 int v4l2_fwnode_endpoint_parse (int /*<<< orphan*/ ,struct v4l2_fwnode_endpoint*) ; 

__attribute__((used)) static int s5pcsis_parse_dt(struct platform_device *pdev,
			    struct csis_state *state)
{
	struct device_node *node = pdev->dev.of_node;
	struct v4l2_fwnode_endpoint endpoint = { .bus_type = 0 };
	int ret;

	if (of_property_read_u32(node, "clock-frequency",
				 &state->clk_frequency))
		state->clk_frequency = DEFAULT_SCLK_CSIS_FREQ;
	if (of_property_read_u32(node, "bus-width",
				 &state->max_num_lanes))
		return -EINVAL;

	node = of_graph_get_next_endpoint(node, NULL);
	if (!node) {
		dev_err(&pdev->dev, "No port node at %pOF\n",
				pdev->dev.of_node);
		return -EINVAL;
	}
	/* Get port node and validate MIPI-CSI channel id. */
	ret = v4l2_fwnode_endpoint_parse(of_fwnode_handle(node), &endpoint);
	if (ret)
		goto err;

	state->index = endpoint.base.port - FIMC_INPUT_MIPI_CSI2_0;
	if (state->index >= CSIS_MAX_ENTITIES) {
		ret = -ENXIO;
		goto err;
	}

	/* Get MIPI CSI-2 bus configuration from the endpoint node. */
	of_property_read_u32(node, "samsung,csis-hs-settle",
					&state->hs_settle);
	state->wclk_ext = of_property_read_bool(node,
					"samsung,csis-wclk");

	state->num_lanes = endpoint.bus.mipi_csi2.num_data_lanes;

err:
	of_node_put(node);
	return ret;
}