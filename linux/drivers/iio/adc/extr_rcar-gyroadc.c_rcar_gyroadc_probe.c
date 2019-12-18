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
struct resource {int dummy; } ;
struct rcar_gyroadc {int model; int /*<<< orphan*/  clk; int /*<<< orphan*/  regs; struct device* dev; } ;
struct device {int /*<<< orphan*/  of_node; } ;
struct platform_device {struct device dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  of_node; struct device* parent; } ;
struct iio_dev {int /*<<< orphan*/  modes; int /*<<< orphan*/ * info; TYPE_1__ dev; int /*<<< orphan*/  name; } ;
typedef  enum rcar_gyroadc_model { ____Placeholder_rcar_gyroadc_model } rcar_gyroadc_model ;

/* Variables and functions */
 int /*<<< orphan*/  DRIVER_NAME ; 
 int ENOMEM ; 
 int EPROBE_DEFER ; 
 int /*<<< orphan*/  INDIO_DIRECT_MODE ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RCAR_GYROADC_RUNTIME_PM_DELAY_MS ; 
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int clk_prepare_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,...) ; 
 int /*<<< orphan*/  devm_clk_get (struct device*,char*) ; 
 struct iio_dev* devm_iio_device_alloc (struct device*,int) ; 
 int /*<<< orphan*/  devm_ioremap_resource (struct device*,struct resource*) ; 
 int iio_device_register (struct iio_dev*) ; 
 struct rcar_gyroadc* iio_priv (struct iio_dev*) ; 
 scalar_t__ of_device_get_match_data (struct device*) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct iio_dev*) ; 
 int /*<<< orphan*/  pm_runtime_disable (struct device*) ; 
 int /*<<< orphan*/  pm_runtime_enable (struct device*) ; 
 int /*<<< orphan*/  pm_runtime_get_sync (struct device*) ; 
 int /*<<< orphan*/  pm_runtime_put_sync (struct device*) ; 
 int /*<<< orphan*/  pm_runtime_set_autosuspend_delay (struct device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_set_suspended (struct device*) ; 
 int /*<<< orphan*/  pm_runtime_use_autosuspend (struct device*) ; 
 int /*<<< orphan*/  rcar_gyroadc_deinit_supplies (struct iio_dev*) ; 
 int /*<<< orphan*/  rcar_gyroadc_hw_init (struct rcar_gyroadc*) ; 
 int /*<<< orphan*/  rcar_gyroadc_hw_start (struct rcar_gyroadc*) ; 
 int /*<<< orphan*/  rcar_gyroadc_hw_stop (struct rcar_gyroadc*) ; 
 int /*<<< orphan*/  rcar_gyroadc_iio_info ; 
 int rcar_gyroadc_init_supplies (struct iio_dev*) ; 
 int rcar_gyroadc_parse_subdevs (struct iio_dev*) ; 

__attribute__((used)) static int rcar_gyroadc_probe(struct platform_device *pdev)
{
	struct device *dev = &pdev->dev;
	struct rcar_gyroadc *priv;
	struct iio_dev *indio_dev;
	struct resource *mem;
	int ret;

	indio_dev = devm_iio_device_alloc(dev, sizeof(*priv));
	if (!indio_dev)
		return -ENOMEM;

	priv = iio_priv(indio_dev);
	priv->dev = dev;

	mem = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	priv->regs = devm_ioremap_resource(dev, mem);
	if (IS_ERR(priv->regs))
		return PTR_ERR(priv->regs);

	priv->clk = devm_clk_get(dev, "fck");
	if (IS_ERR(priv->clk)) {
		ret = PTR_ERR(priv->clk);
		if (ret != -EPROBE_DEFER)
			dev_err(dev, "Failed to get IF clock (ret=%i)\n", ret);
		return ret;
	}

	ret = rcar_gyroadc_parse_subdevs(indio_dev);
	if (ret)
		return ret;

	ret = rcar_gyroadc_init_supplies(indio_dev);
	if (ret)
		return ret;

	priv->model = (enum rcar_gyroadc_model)
		of_device_get_match_data(&pdev->dev);

	platform_set_drvdata(pdev, indio_dev);

	indio_dev->name = DRIVER_NAME;
	indio_dev->dev.parent = dev;
	indio_dev->dev.of_node = pdev->dev.of_node;
	indio_dev->info = &rcar_gyroadc_iio_info;
	indio_dev->modes = INDIO_DIRECT_MODE;

	ret = clk_prepare_enable(priv->clk);
	if (ret) {
		dev_err(dev, "Could not prepare or enable the IF clock.\n");
		goto err_clk_if_enable;
	}

	pm_runtime_set_autosuspend_delay(dev, RCAR_GYROADC_RUNTIME_PM_DELAY_MS);
	pm_runtime_use_autosuspend(dev);
	pm_runtime_enable(dev);

	pm_runtime_get_sync(dev);
	rcar_gyroadc_hw_init(priv);
	rcar_gyroadc_hw_start(priv);

	ret = iio_device_register(indio_dev);
	if (ret) {
		dev_err(dev, "Couldn't register IIO device.\n");
		goto err_iio_device_register;
	}

	pm_runtime_put_sync(dev);

	return 0;

err_iio_device_register:
	rcar_gyroadc_hw_stop(priv);
	pm_runtime_put_sync(dev);
	pm_runtime_disable(dev);
	pm_runtime_set_suspended(dev);
	clk_disable_unprepare(priv->clk);
err_clk_if_enable:
	rcar_gyroadc_deinit_supplies(indio_dev);

	return ret;
}