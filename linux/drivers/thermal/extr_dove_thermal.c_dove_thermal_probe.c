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
struct thermal_zone_device {int dummy; } ;
struct resource {int dummy; } ;
struct platform_device {int /*<<< orphan*/  dev; } ;
struct dove_thermal_priv {struct thermal_zone_device* control; struct thermal_zone_device* sensor; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 scalar_t__ IS_ERR (struct thermal_zone_device*) ; 
 int PTR_ERR (struct thermal_zone_device*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 void* devm_ioremap_resource (int /*<<< orphan*/ *,struct resource*) ; 
 struct dove_thermal_priv* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int dove_init_sensor (struct dove_thermal_priv*) ; 
 int /*<<< orphan*/  ops ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct thermal_zone_device*) ; 
 struct thermal_zone_device* thermal_zone_device_register (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct dove_thermal_priv*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int dove_thermal_probe(struct platform_device *pdev)
{
	struct thermal_zone_device *thermal = NULL;
	struct dove_thermal_priv *priv;
	struct resource *res;
	int ret;

	priv = devm_kzalloc(&pdev->dev, sizeof(*priv), GFP_KERNEL);
	if (!priv)
		return -ENOMEM;

	res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	priv->sensor = devm_ioremap_resource(&pdev->dev, res);
	if (IS_ERR(priv->sensor))
		return PTR_ERR(priv->sensor);

	res = platform_get_resource(pdev, IORESOURCE_MEM, 1);
	priv->control = devm_ioremap_resource(&pdev->dev, res);
	if (IS_ERR(priv->control))
		return PTR_ERR(priv->control);

	ret = dove_init_sensor(priv);
	if (ret) {
		dev_err(&pdev->dev, "Failed to initialize sensor\n");
		return ret;
	}

	thermal = thermal_zone_device_register("dove_thermal", 0, 0,
					       priv, &ops, NULL, 0, 0);
	if (IS_ERR(thermal)) {
		dev_err(&pdev->dev,
			"Failed to register thermal zone device\n");
		return PTR_ERR(thermal);
	}

	platform_set_drvdata(pdev, thermal);

	return 0;
}