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
struct brcmstb_thermal_priv {struct thermal_zone_device* thermal; int /*<<< orphan*/ * dev; struct thermal_zone_device* tmon_base; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRV_NAME ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 int /*<<< orphan*/  IRQF_ONESHOT ; 
 scalar_t__ IS_ERR (struct thermal_zone_device*) ; 
 int PTR_ERR (struct thermal_zone_device*) ; 
 int /*<<< orphan*/  brcmstb_tmon_irq_thread ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*) ; 
 struct thermal_zone_device* devm_ioremap_resource (int /*<<< orphan*/ *,struct resource*) ; 
 struct brcmstb_thermal_priv* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int devm_request_threaded_irq (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct brcmstb_thermal_priv*) ; 
 struct thermal_zone_device* devm_thermal_zone_of_sensor_register (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct brcmstb_thermal_priv*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  of_ops ; 
 int platform_get_irq (struct platform_device*,int /*<<< orphan*/ ) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct brcmstb_thermal_priv*) ; 

__attribute__((used)) static int brcmstb_thermal_probe(struct platform_device *pdev)
{
	struct thermal_zone_device *thermal;
	struct brcmstb_thermal_priv *priv;
	struct resource *res;
	int irq, ret;

	priv = devm_kzalloc(&pdev->dev, sizeof(*priv), GFP_KERNEL);
	if (!priv)
		return -ENOMEM;

	res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	priv->tmon_base = devm_ioremap_resource(&pdev->dev, res);
	if (IS_ERR(priv->tmon_base))
		return PTR_ERR(priv->tmon_base);

	priv->dev = &pdev->dev;
	platform_set_drvdata(pdev, priv);

	thermal = devm_thermal_zone_of_sensor_register(&pdev->dev, 0, priv,
						       &of_ops);
	if (IS_ERR(thermal)) {
		ret = PTR_ERR(thermal);
		dev_err(&pdev->dev, "could not register sensor: %d\n", ret);
		return ret;
	}

	priv->thermal = thermal;

	irq = platform_get_irq(pdev, 0);
	if (irq < 0) {
		dev_err(&pdev->dev, "could not get IRQ\n");
		return irq;
	}
	ret = devm_request_threaded_irq(&pdev->dev, irq, NULL,
					brcmstb_tmon_irq_thread, IRQF_ONESHOT,
					DRV_NAME, priv);
	if (ret < 0) {
		dev_err(&pdev->dev, "could not request IRQ: %d\n", ret);
		return ret;
	}

	dev_info(&pdev->dev, "registered AVS TMON of-sensor driver\n");

	return 0;
}