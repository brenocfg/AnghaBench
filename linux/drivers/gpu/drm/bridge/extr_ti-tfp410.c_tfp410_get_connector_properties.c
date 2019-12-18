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
struct tfp410 {TYPE_1__* dev; int /*<<< orphan*/  ddc; int /*<<< orphan*/ * hpd; int /*<<< orphan*/  connector_type; } ;
struct device_node {int /*<<< orphan*/  fwnode; } ;
struct TYPE_2__ {int /*<<< orphan*/  of_node; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_MODE_CONNECTOR_DVID ; 
 int /*<<< orphan*/  DRM_MODE_CONNECTOR_HDMIA ; 
 int ENODEV ; 
 int ENOENT ; 
 int EPROBE_DEFER ; 
 int /*<<< orphan*/  GPIOD_IN ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ *) ; 
 int PTR_ERR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_info (TYPE_1__*,char*) ; 
 int /*<<< orphan*/ * fwnode_get_named_gpiod (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 scalar_t__ of_device_is_compatible (struct device_node*,char*) ; 
 int /*<<< orphan*/  of_get_i2c_adapter_by_node (struct device_node*) ; 
 struct device_node* of_graph_get_remote_node (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  of_node_put (struct device_node*) ; 
 struct device_node* of_parse_phandle (struct device_node*,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int tfp410_get_connector_properties(struct tfp410 *dvi)
{
	struct device_node *connector_node, *ddc_phandle;
	int ret = 0;

	/* port@1 is the connector node */
	connector_node = of_graph_get_remote_node(dvi->dev->of_node, 1, -1);
	if (!connector_node)
		return -ENODEV;

	if (of_device_is_compatible(connector_node, "hdmi-connector"))
		dvi->connector_type = DRM_MODE_CONNECTOR_HDMIA;
	else
		dvi->connector_type = DRM_MODE_CONNECTOR_DVID;

	dvi->hpd = fwnode_get_named_gpiod(&connector_node->fwnode,
					"hpd-gpios", 0, GPIOD_IN, "hpd");
	if (IS_ERR(dvi->hpd)) {
		ret = PTR_ERR(dvi->hpd);
		dvi->hpd = NULL;
		if (ret == -ENOENT)
			ret = 0;
		else
			goto fail;
	}

	ddc_phandle = of_parse_phandle(connector_node, "ddc-i2c-bus", 0);
	if (!ddc_phandle)
		goto fail;

	dvi->ddc = of_get_i2c_adapter_by_node(ddc_phandle);
	if (dvi->ddc)
		dev_info(dvi->dev, "Connector's ddc i2c bus found\n");
	else
		ret = -EPROBE_DEFER;

	of_node_put(ddc_phandle);

fail:
	of_node_put(connector_node);
	return ret;
}