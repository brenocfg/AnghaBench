#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct resource {int dummy; } ;
struct device {struct device_node* of_node; } ;
struct platform_device {struct device dev; } ;
struct device_node {int dummy; } ;
struct devbus_write_params {int dummy; } ;
struct devbus_read_params {int dummy; } ;
struct devbus {int tick_ps; struct device* dev; struct clk* base; } ;
struct clk {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 scalar_t__ IS_ERR (struct clk*) ; 
 int PTR_ERR (struct clk*) ; 
 int clk_get_rate (struct clk*) ; 
 int /*<<< orphan*/  clk_prepare_enable (struct clk*) ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*,int) ; 
 int /*<<< orphan*/  devbus_armada_set_timing_params (struct devbus*,struct device_node*,struct devbus_read_params*,struct devbus_write_params*) ; 
 int devbus_get_timing_params (struct devbus*,struct device_node*,struct devbus_read_params*,struct devbus_write_params*) ; 
 int /*<<< orphan*/  devbus_orion_set_timing_params (struct devbus*,struct device_node*,struct devbus_read_params*,struct devbus_write_params*) ; 
 struct clk* devm_clk_get (struct device*,int /*<<< orphan*/ *) ; 
 struct clk* devm_ioremap_resource (struct device*,struct resource*) ; 
 struct devbus* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 scalar_t__ of_device_is_compatible (struct device_node*,char*) ; 
 int of_platform_populate (struct device_node*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct device*) ; 
 int /*<<< orphan*/  of_property_read_bool (struct device_node*,char*) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mvebu_devbus_probe(struct platform_device *pdev)
{
	struct device *dev = &pdev->dev;
	struct device_node *node = pdev->dev.of_node;
	struct devbus_read_params r;
	struct devbus_write_params w;
	struct devbus *devbus;
	struct resource *res;
	struct clk *clk;
	unsigned long rate;
	int err;

	devbus = devm_kzalloc(&pdev->dev, sizeof(struct devbus), GFP_KERNEL);
	if (!devbus)
		return -ENOMEM;

	devbus->dev = dev;
	res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	devbus->base = devm_ioremap_resource(&pdev->dev, res);
	if (IS_ERR(devbus->base))
		return PTR_ERR(devbus->base);

	clk = devm_clk_get(&pdev->dev, NULL);
	if (IS_ERR(clk))
		return PTR_ERR(clk);
	clk_prepare_enable(clk);

	/*
	 * Obtain clock period in picoseconds,
	 * we need this in order to convert timing
	 * parameters from cycles to picoseconds.
	 */
	rate = clk_get_rate(clk) / 1000;
	devbus->tick_ps = 1000000000 / rate;

	dev_dbg(devbus->dev, "Setting timing parameter, tick is %lu ps\n",
		devbus->tick_ps);

	if (!of_property_read_bool(node, "devbus,keep-config")) {
		/* Read the Device Tree node */
		err = devbus_get_timing_params(devbus, node, &r, &w);
		if (err < 0)
			return err;

		/* Set the new timing parameters */
		if (of_device_is_compatible(node, "marvell,orion-devbus"))
			devbus_orion_set_timing_params(devbus, node, &r, &w);
		else
			devbus_armada_set_timing_params(devbus, node, &r, &w);
	}

	/*
	 * We need to create a child device explicitly from here to
	 * guarantee that the child will be probed after the timing
	 * parameters for the bus are written.
	 */
	err = of_platform_populate(node, NULL, NULL, dev);
	if (err < 0)
		return err;

	return 0;
}