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
struct TYPE_4__ {unsigned int flags; } ;
struct TYPE_5__ {TYPE_1__ parallel; } ;
struct v4l2_fwnode_endpoint {TYPE_2__ bus; int /*<<< orphan*/  bus_type; } ;
struct tvp7002_config {int hs_polarity; int vs_polarity; int clk_polarity; int fid_polarity; int sog_polarity; } ;
struct TYPE_6__ {int /*<<< orphan*/  of_node; struct tvp7002_config* platform_data; } ;
struct i2c_client {TYPE_3__ dev; } ;
struct device_node {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CONFIG_OF ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IS_ENABLED (int /*<<< orphan*/ ) ; 
 unsigned int V4L2_MBUS_FIELD_EVEN_HIGH ; 
 unsigned int V4L2_MBUS_HSYNC_ACTIVE_HIGH ; 
 unsigned int V4L2_MBUS_PCLK_SAMPLE_RISING ; 
 unsigned int V4L2_MBUS_VIDEO_SOG_ACTIVE_HIGH ; 
 unsigned int V4L2_MBUS_VSYNC_ACTIVE_HIGH ; 
 struct tvp7002_config* devm_kzalloc (TYPE_3__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  of_fwnode_handle (struct device_node*) ; 
 struct device_node* of_graph_get_next_endpoint (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  of_node_put (struct device_node*) ; 
 scalar_t__ v4l2_fwnode_endpoint_parse (int /*<<< orphan*/ ,struct v4l2_fwnode_endpoint*) ; 

__attribute__((used)) static struct tvp7002_config *
tvp7002_get_pdata(struct i2c_client *client)
{
	struct v4l2_fwnode_endpoint bus_cfg = { .bus_type = 0 };
	struct tvp7002_config *pdata = NULL;
	struct device_node *endpoint;
	unsigned int flags;

	if (!IS_ENABLED(CONFIG_OF) || !client->dev.of_node)
		return client->dev.platform_data;

	endpoint = of_graph_get_next_endpoint(client->dev.of_node, NULL);
	if (!endpoint)
		return NULL;

	if (v4l2_fwnode_endpoint_parse(of_fwnode_handle(endpoint), &bus_cfg))
		goto done;

	pdata = devm_kzalloc(&client->dev, sizeof(*pdata), GFP_KERNEL);
	if (!pdata)
		goto done;

	flags = bus_cfg.bus.parallel.flags;

	if (flags & V4L2_MBUS_HSYNC_ACTIVE_HIGH)
		pdata->hs_polarity = 1;

	if (flags & V4L2_MBUS_VSYNC_ACTIVE_HIGH)
		pdata->vs_polarity = 1;

	if (flags & V4L2_MBUS_PCLK_SAMPLE_RISING)
		pdata->clk_polarity = 1;

	if (flags & V4L2_MBUS_FIELD_EVEN_HIGH)
		pdata->fid_polarity = 1;

	if (flags & V4L2_MBUS_VIDEO_SOG_ACTIVE_HIGH)
		pdata->sog_polarity = 1;

done:
	of_node_put(endpoint);
	return pdata;
}