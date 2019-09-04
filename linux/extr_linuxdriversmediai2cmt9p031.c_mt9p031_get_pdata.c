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
struct mt9p031_platform_data {int /*<<< orphan*/  target_freq; int /*<<< orphan*/  ext_freq; } ;
struct TYPE_2__ {int /*<<< orphan*/  of_node; struct mt9p031_platform_data* platform_data; } ;
struct i2c_client {TYPE_1__ dev; } ;
struct device_node {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CONFIG_OF ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IS_ENABLED (int /*<<< orphan*/ ) ; 
 struct mt9p031_platform_data* devm_kzalloc (TYPE_1__*,int,int /*<<< orphan*/ ) ; 
 struct device_node* of_graph_get_next_endpoint (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  of_node_put (struct device_node*) ; 
 int /*<<< orphan*/  of_property_read_u32 (struct device_node*,char*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct mt9p031_platform_data *
mt9p031_get_pdata(struct i2c_client *client)
{
	struct mt9p031_platform_data *pdata;
	struct device_node *np;

	if (!IS_ENABLED(CONFIG_OF) || !client->dev.of_node)
		return client->dev.platform_data;

	np = of_graph_get_next_endpoint(client->dev.of_node, NULL);
	if (!np)
		return NULL;

	pdata = devm_kzalloc(&client->dev, sizeof(*pdata), GFP_KERNEL);
	if (!pdata)
		goto done;

	of_property_read_u32(np, "input-clock-frequency", &pdata->ext_freq);
	of_property_read_u32(np, "pixel-clock-frequency", &pdata->target_freq);

done:
	of_node_put(np);
	return pdata;
}