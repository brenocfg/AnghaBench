#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct thermal_zone_device {int /*<<< orphan*/  device; } ;
struct spear_thermal_dev {int flags; struct thermal_zone_device* clk; struct thermal_zone_device* thermal_base; } ;
struct resource {int dummy; } ;
struct TYPE_5__ {struct device_node* of_node; } ;
struct platform_device {TYPE_1__ dev; } ;
struct device_node {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 scalar_t__ IS_ERR (struct thermal_zone_device*) ; 
 int PTR_ERR (struct thermal_zone_device*) ; 
 int /*<<< orphan*/  clk_disable (struct thermal_zone_device*) ; 
 int clk_enable (struct thermal_zone_device*) ; 
 int /*<<< orphan*/  dev_err (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,struct thermal_zone_device*) ; 
 struct thermal_zone_device* devm_clk_get (TYPE_1__*,int /*<<< orphan*/ *) ; 
 struct thermal_zone_device* devm_ioremap_resource (TYPE_1__*,struct resource*) ; 
 struct spear_thermal_dev* devm_kzalloc (TYPE_1__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  of_property_read_u32 (struct device_node*,char*,int*) ; 
 int /*<<< orphan*/  ops ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct thermal_zone_device*) ; 
 struct thermal_zone_device* thermal_zone_device_register (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct spear_thermal_dev*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writel_relaxed (int,struct thermal_zone_device*) ; 

__attribute__((used)) static int spear_thermal_probe(struct platform_device *pdev)
{
	struct thermal_zone_device *spear_thermal = NULL;
	struct spear_thermal_dev *stdev;
	struct device_node *np = pdev->dev.of_node;
	struct resource *res;
	int ret = 0, val;

	if (!np || !of_property_read_u32(np, "st,thermal-flags", &val)) {
		dev_err(&pdev->dev, "Failed: DT Pdata not passed\n");
		return -EINVAL;
	}

	stdev = devm_kzalloc(&pdev->dev, sizeof(*stdev), GFP_KERNEL);
	if (!stdev)
		return -ENOMEM;

	/* Enable thermal sensor */
	res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	stdev->thermal_base = devm_ioremap_resource(&pdev->dev, res);
	if (IS_ERR(stdev->thermal_base))
		return PTR_ERR(stdev->thermal_base);

	stdev->clk = devm_clk_get(&pdev->dev, NULL);
	if (IS_ERR(stdev->clk)) {
		dev_err(&pdev->dev, "Can't get clock\n");
		return PTR_ERR(stdev->clk);
	}

	ret = clk_enable(stdev->clk);
	if (ret) {
		dev_err(&pdev->dev, "Can't enable clock\n");
		return ret;
	}

	stdev->flags = val;
	writel_relaxed(stdev->flags, stdev->thermal_base);

	spear_thermal = thermal_zone_device_register("spear_thermal", 0, 0,
				stdev, &ops, NULL, 0, 0);
	if (IS_ERR(spear_thermal)) {
		dev_err(&pdev->dev, "thermal zone device is NULL\n");
		ret = PTR_ERR(spear_thermal);
		goto disable_clk;
	}

	platform_set_drvdata(pdev, spear_thermal);

	dev_info(&spear_thermal->device, "Thermal Sensor Loaded at: 0x%p.\n",
			stdev->thermal_base);

	return 0;

disable_clk:
	clk_disable(stdev->clk);

	return ret;
}