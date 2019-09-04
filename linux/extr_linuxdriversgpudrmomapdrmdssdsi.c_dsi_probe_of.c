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
typedef  scalar_t__ u32 ;
struct property {int dummy; } ;
struct omap_dsi_pin_config {int num_pins; int* pins; } ;
struct dsi_data {int num_lanes_supported; TYPE_1__* dev; int /*<<< orphan*/  output; } ;
struct device_node {int dummy; } ;
struct TYPE_2__ {struct device_node* of_node; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  dev_err (TYPE_1__*,char*) ; 
 int dsi_configure_pins (int /*<<< orphan*/ *,struct omap_dsi_pin_config*) ; 
 struct property* of_find_property (struct device_node*,char*,int*) ; 
 struct device_node* of_graph_get_endpoint_by_regs (struct device_node*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  of_node_put (struct device_node*) ; 
 int of_property_read_u32_array (struct device_node*,char*,scalar_t__*,int) ; 

__attribute__((used)) static int dsi_probe_of(struct dsi_data *dsi)
{
	struct device_node *node = dsi->dev->of_node;
	struct property *prop;
	u32 lane_arr[10];
	int len, num_pins;
	int r, i;
	struct device_node *ep;
	struct omap_dsi_pin_config pin_cfg;

	ep = of_graph_get_endpoint_by_regs(node, 0, 0);
	if (!ep)
		return 0;

	prop = of_find_property(ep, "lanes", &len);
	if (prop == NULL) {
		dev_err(dsi->dev, "failed to find lane data\n");
		r = -EINVAL;
		goto err;
	}

	num_pins = len / sizeof(u32);

	if (num_pins < 4 || num_pins % 2 != 0 ||
		num_pins > dsi->num_lanes_supported * 2) {
		dev_err(dsi->dev, "bad number of lanes\n");
		r = -EINVAL;
		goto err;
	}

	r = of_property_read_u32_array(ep, "lanes", lane_arr, num_pins);
	if (r) {
		dev_err(dsi->dev, "failed to read lane data\n");
		goto err;
	}

	pin_cfg.num_pins = num_pins;
	for (i = 0; i < num_pins; ++i)
		pin_cfg.pins[i] = (int)lane_arr[i];

	r = dsi_configure_pins(&dsi->output, &pin_cfg);
	if (r) {
		dev_err(dsi->dev, "failed to configure pins");
		goto err;
	}

	of_node_put(ep);

	return 0;

err:
	of_node_put(ep);
	return r;
}