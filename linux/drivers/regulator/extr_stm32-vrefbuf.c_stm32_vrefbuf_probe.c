#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_1__ ;

/* Type definitions */
struct stm32_vrefbuf {struct regulator_dev* clk; struct regulator_dev* base; TYPE_1__* dev; } ;
struct resource {int dummy; } ;
struct regulator_dev {int dummy; } ;
struct regulator_config {int /*<<< orphan*/  init_data; int /*<<< orphan*/  of_node; struct stm32_vrefbuf* driver_data; TYPE_1__* dev; } ;
struct TYPE_16__ {int /*<<< orphan*/  of_node; } ;
struct platform_device {TYPE_1__ dev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 scalar_t__ IS_ERR (struct regulator_dev*) ; 
 int PTR_ERR (struct regulator_dev*) ; 
 int /*<<< orphan*/  STM32_VREFBUF_AUTO_SUSPEND_DELAY_MS ; 
 int /*<<< orphan*/  clk_disable_unprepare (struct regulator_dev*) ; 
 int clk_prepare_enable (struct regulator_dev*) ; 
 int /*<<< orphan*/  dev_err (TYPE_1__*,char*,int) ; 
 struct regulator_dev* devm_clk_get (TYPE_1__*,int /*<<< orphan*/ *) ; 
 struct regulator_dev* devm_ioremap_resource (TYPE_1__*,struct resource*) ; 
 struct stm32_vrefbuf* devm_kzalloc (TYPE_1__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  of_get_regulator_init_data (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct regulator_dev*) ; 
 int /*<<< orphan*/  pm_runtime_disable (TYPE_1__*) ; 
 int /*<<< orphan*/  pm_runtime_enable (TYPE_1__*) ; 
 int /*<<< orphan*/  pm_runtime_get_noresume (TYPE_1__*) ; 
 int /*<<< orphan*/  pm_runtime_mark_last_busy (TYPE_1__*) ; 
 int /*<<< orphan*/  pm_runtime_put_autosuspend (TYPE_1__*) ; 
 int /*<<< orphan*/  pm_runtime_put_noidle (TYPE_1__*) ; 
 int /*<<< orphan*/  pm_runtime_set_active (TYPE_1__*) ; 
 int /*<<< orphan*/  pm_runtime_set_autosuspend_delay (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_set_suspended (TYPE_1__*) ; 
 int /*<<< orphan*/  pm_runtime_use_autosuspend (TYPE_1__*) ; 
 struct regulator_dev* regulator_register (int /*<<< orphan*/ *,struct regulator_config*) ; 
 int /*<<< orphan*/  stm32_vrefbuf_regu ; 

__attribute__((used)) static int stm32_vrefbuf_probe(struct platform_device *pdev)
{
	struct resource *res;
	struct stm32_vrefbuf *priv;
	struct regulator_config config = { };
	struct regulator_dev *rdev;
	int ret;

	priv = devm_kzalloc(&pdev->dev, sizeof(*priv), GFP_KERNEL);
	if (!priv)
		return -ENOMEM;
	priv->dev = &pdev->dev;

	res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	priv->base = devm_ioremap_resource(&pdev->dev, res);
	if (IS_ERR(priv->base))
		return PTR_ERR(priv->base);

	priv->clk = devm_clk_get(&pdev->dev, NULL);
	if (IS_ERR(priv->clk))
		return PTR_ERR(priv->clk);

	pm_runtime_get_noresume(&pdev->dev);
	pm_runtime_set_active(&pdev->dev);
	pm_runtime_set_autosuspend_delay(&pdev->dev,
					 STM32_VREFBUF_AUTO_SUSPEND_DELAY_MS);
	pm_runtime_use_autosuspend(&pdev->dev);
	pm_runtime_enable(&pdev->dev);

	ret = clk_prepare_enable(priv->clk);
	if (ret) {
		dev_err(&pdev->dev, "clk prepare failed with error %d\n", ret);
		goto err_pm_stop;
	}

	config.dev = &pdev->dev;
	config.driver_data = priv;
	config.of_node = pdev->dev.of_node;
	config.init_data = of_get_regulator_init_data(&pdev->dev,
						      pdev->dev.of_node,
						      &stm32_vrefbuf_regu);

	rdev = regulator_register(&stm32_vrefbuf_regu, &config);
	if (IS_ERR(rdev)) {
		ret = PTR_ERR(rdev);
		dev_err(&pdev->dev, "register failed with error %d\n", ret);
		goto err_clk_dis;
	}
	platform_set_drvdata(pdev, rdev);

	pm_runtime_mark_last_busy(&pdev->dev);
	pm_runtime_put_autosuspend(&pdev->dev);

	return 0;

err_clk_dis:
	clk_disable_unprepare(priv->clk);
err_pm_stop:
	pm_runtime_disable(&pdev->dev);
	pm_runtime_set_suspended(&pdev->dev);
	pm_runtime_put_noidle(&pdev->dev);

	return ret;
}