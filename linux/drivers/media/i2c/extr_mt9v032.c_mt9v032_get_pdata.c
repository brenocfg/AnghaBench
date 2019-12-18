#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u64 ;
struct TYPE_5__ {int flags; } ;
struct TYPE_6__ {TYPE_1__ parallel; } ;
struct v4l2_fwnode_endpoint {TYPE_2__ bus; int /*<<< orphan*/  bus_type; } ;
struct property {int length; } ;
struct mt9v032_platform_data {int clk_pol; int /*<<< orphan*/  link_def_freq; int /*<<< orphan*/ * link_freqs; } ;
struct TYPE_7__ {int /*<<< orphan*/  of_node; struct mt9v032_platform_data* platform_data; } ;
struct i2c_client {TYPE_3__ dev; } ;
struct device_node {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CONFIG_OF ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IS_ENABLED (int /*<<< orphan*/ ) ; 
 int V4L2_MBUS_PCLK_SAMPLE_RISING ; 
 int /*<<< orphan*/ * devm_kcalloc (TYPE_3__*,size_t,int,int /*<<< orphan*/ ) ; 
 struct mt9v032_platform_data* devm_kzalloc (TYPE_3__*,int,int /*<<< orphan*/ ) ; 
 struct property* of_find_property (struct device_node*,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  of_fwnode_handle (struct device_node*) ; 
 struct device_node* of_graph_get_next_endpoint (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  of_node_put (struct device_node*) ; 
 scalar_t__ of_property_read_u64_array (struct device_node*,char*,int /*<<< orphan*/ *,size_t) ; 
 scalar_t__ v4l2_fwnode_endpoint_parse (int /*<<< orphan*/ ,struct v4l2_fwnode_endpoint*) ; 

__attribute__((used)) static struct mt9v032_platform_data *
mt9v032_get_pdata(struct i2c_client *client)
{
	struct mt9v032_platform_data *pdata = NULL;
	struct v4l2_fwnode_endpoint endpoint = { .bus_type = 0 };
	struct device_node *np;
	struct property *prop;

	if (!IS_ENABLED(CONFIG_OF) || !client->dev.of_node)
		return client->dev.platform_data;

	np = of_graph_get_next_endpoint(client->dev.of_node, NULL);
	if (!np)
		return NULL;

	if (v4l2_fwnode_endpoint_parse(of_fwnode_handle(np), &endpoint) < 0)
		goto done;

	pdata = devm_kzalloc(&client->dev, sizeof(*pdata), GFP_KERNEL);
	if (!pdata)
		goto done;

	prop = of_find_property(np, "link-frequencies", NULL);
	if (prop) {
		u64 *link_freqs;
		size_t size = prop->length / sizeof(*link_freqs);

		link_freqs = devm_kcalloc(&client->dev, size,
					  sizeof(*link_freqs), GFP_KERNEL);
		if (!link_freqs)
			goto done;

		if (of_property_read_u64_array(np, "link-frequencies",
					       link_freqs, size) < 0)
			goto done;

		pdata->link_freqs = link_freqs;
		pdata->link_def_freq = link_freqs[0];
	}

	pdata->clk_pol = !!(endpoint.bus.parallel.flags &
			    V4L2_MBUS_PCLK_SAMPLE_RISING);

done:
	of_node_put(np);
	return pdata;
}