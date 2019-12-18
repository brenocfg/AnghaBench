#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct zx2967_thermal_priv {TYPE_2__* clk_topcrm; TYPE_2__* clk_apb; int /*<<< orphan*/ * dev; TYPE_2__* tzd; int /*<<< orphan*/  lock; TYPE_2__* regs; } ;
struct resource {int dummy; } ;
struct platform_device {int /*<<< orphan*/  dev; } ;
struct TYPE_10__ {TYPE_1__* tzp; } ;
struct TYPE_9__ {scalar_t__ slope; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 scalar_t__ IS_ERR (TYPE_2__*) ; 
 int PTR_ERR (TYPE_2__*) ; 
 int /*<<< orphan*/  clk_disable_unprepare (TYPE_2__*) ; 
 int clk_prepare_enable (TYPE_2__*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,...) ; 
 void* devm_clk_get (int /*<<< orphan*/ *,char*) ; 
 TYPE_2__* devm_ioremap_resource (int /*<<< orphan*/ *,struct resource*) ; 
 struct zx2967_thermal_priv* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct zx2967_thermal_priv*) ; 
 TYPE_2__* thermal_zone_of_sensor_register (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct zx2967_thermal_priv*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  thermal_zone_of_sensor_unregister (int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  zx2967_of_thermal_ops ; 

__attribute__((used)) static int zx2967_thermal_probe(struct platform_device *pdev)
{
	struct zx2967_thermal_priv *priv;
	struct resource *res;
	int ret;

	priv = devm_kzalloc(&pdev->dev, sizeof(*priv), GFP_KERNEL);
	if (!priv)
		return -ENOMEM;

	res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	priv->regs = devm_ioremap_resource(&pdev->dev, res);
	if (IS_ERR(priv->regs))
		return PTR_ERR(priv->regs);

	priv->clk_topcrm = devm_clk_get(&pdev->dev, "topcrm");
	if (IS_ERR(priv->clk_topcrm)) {
		ret = PTR_ERR(priv->clk_topcrm);
		dev_err(&pdev->dev, "failed to get topcrm clock: %d\n", ret);
		return ret;
	}

	ret = clk_prepare_enable(priv->clk_topcrm);
	if (ret) {
		dev_err(&pdev->dev, "failed to enable topcrm clock: %d\n",
			ret);
		return ret;
	}

	priv->clk_apb = devm_clk_get(&pdev->dev, "apb");
	if (IS_ERR(priv->clk_apb)) {
		ret = PTR_ERR(priv->clk_apb);
		dev_err(&pdev->dev, "failed to get apb clock: %d\n", ret);
		goto disable_clk_topcrm;
	}

	ret = clk_prepare_enable(priv->clk_apb);
	if (ret) {
		dev_err(&pdev->dev, "failed to enable apb clock: %d\n",
			ret);
		goto disable_clk_topcrm;
	}

	mutex_init(&priv->lock);
	priv->tzd = thermal_zone_of_sensor_register(&pdev->dev,
					0, priv, &zx2967_of_thermal_ops);

	if (IS_ERR(priv->tzd)) {
		ret = PTR_ERR(priv->tzd);
		dev_err(&pdev->dev, "failed to register sensor: %d\n", ret);
		goto disable_clk_all;
	}

	if (priv->tzd->tzp->slope == 0) {
		thermal_zone_of_sensor_unregister(&pdev->dev, priv->tzd);
		dev_err(&pdev->dev, "coefficients of sensor is invalid\n");
		ret = -EINVAL;
		goto disable_clk_all;
	}

	priv->dev = &pdev->dev;
	platform_set_drvdata(pdev, priv);

	return 0;

disable_clk_all:
	clk_disable_unprepare(priv->clk_apb);
disable_clk_topcrm:
	clk_disable_unprepare(priv->clk_topcrm);
	return ret;
}