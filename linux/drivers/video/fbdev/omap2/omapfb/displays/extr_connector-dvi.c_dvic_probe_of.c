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
struct TYPE_2__ {struct device_node* of_node; } ;
struct platform_device {TYPE_1__ dev; } ;
struct panel_drv_data {struct i2c_adapter* i2c_adapter; struct omap_dss_device* in; } ;
struct omap_dss_device {int dummy; } ;
struct i2c_adapter {int dummy; } ;
struct device_node {int dummy; } ;

/* Variables and functions */
 int EPROBE_DEFER ; 
 scalar_t__ IS_ERR (struct omap_dss_device*) ; 
 int PTR_ERR (struct omap_dss_device*) ; 
 int /*<<< orphan*/  dev_err (TYPE_1__*,char*) ; 
 struct i2c_adapter* of_get_i2c_adapter_by_node (struct device_node*) ; 
 struct device_node* of_parse_phandle (struct device_node*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  omap_dss_put_device (struct omap_dss_device*) ; 
 struct omap_dss_device* omapdss_of_find_source_for_first_ep (struct device_node*) ; 
 struct panel_drv_data* platform_get_drvdata (struct platform_device*) ; 

__attribute__((used)) static int dvic_probe_of(struct platform_device *pdev)
{
	struct panel_drv_data *ddata = platform_get_drvdata(pdev);
	struct device_node *node = pdev->dev.of_node;
	struct omap_dss_device *in;
	struct device_node *adapter_node;
	struct i2c_adapter *adapter;

	in = omapdss_of_find_source_for_first_ep(node);
	if (IS_ERR(in)) {
		dev_err(&pdev->dev, "failed to find video source\n");
		return PTR_ERR(in);
	}

	ddata->in = in;

	adapter_node = of_parse_phandle(node, "ddc-i2c-bus", 0);
	if (adapter_node) {
		adapter = of_get_i2c_adapter_by_node(adapter_node);
		if (adapter == NULL) {
			dev_err(&pdev->dev, "failed to parse ddc-i2c-bus\n");
			omap_dss_put_device(ddata->in);
			return -EPROBE_DEFER;
		}

		ddata->i2c_adapter = adapter;
	}

	return 0;
}