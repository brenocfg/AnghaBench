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
struct platform_device {int /*<<< orphan*/  dev; } ;
struct TYPE_2__ {int /*<<< orphan*/ * parent; } ;
struct iio_dev {int /*<<< orphan*/  channels; int /*<<< orphan*/  num_channels; int /*<<< orphan*/ * info; int /*<<< orphan*/  modes; int /*<<< orphan*/  name; TYPE_1__ dev; } ;
struct ep93xx_adc_priv {int lastch; int /*<<< orphan*/  clk; int /*<<< orphan*/  lock; int /*<<< orphan*/  base; } ;
struct clk {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  INDIO_DIRECT_MODE ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clk_disable (int /*<<< orphan*/ ) ; 
 int clk_enable (int /*<<< orphan*/ ) ; 
 struct clk* clk_get_parent (int /*<<< orphan*/ ) ; 
 int clk_get_rate (struct clk*) ; 
 int clk_set_rate (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  dev_name (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  devm_clk_get (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct iio_dev* devm_iio_device_alloc (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  devm_ioremap_resource (int /*<<< orphan*/ *,struct resource*) ; 
 int /*<<< orphan*/  ep93xx_adc_channels ; 
 int /*<<< orphan*/  ep93xx_adc_info ; 
 int iio_device_register (struct iio_dev*) ; 
 struct ep93xx_adc_priv* iio_priv (struct iio_dev*) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct iio_dev*) ; 

__attribute__((used)) static int ep93xx_adc_probe(struct platform_device *pdev)
{
	int ret;
	struct iio_dev *iiodev;
	struct ep93xx_adc_priv *priv;
	struct clk *pclk;
	struct resource *res;

	iiodev = devm_iio_device_alloc(&pdev->dev, sizeof(*priv));
	if (!iiodev)
		return -ENOMEM;
	priv = iio_priv(iiodev);

	res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	priv->base = devm_ioremap_resource(&pdev->dev, res);
	if (IS_ERR(priv->base)) {
		dev_err(&pdev->dev, "Cannot map memory resource\n");
		return PTR_ERR(priv->base);
	}

	iiodev->dev.parent = &pdev->dev;
	iiodev->name = dev_name(&pdev->dev);
	iiodev->modes = INDIO_DIRECT_MODE;
	iiodev->info = &ep93xx_adc_info;
	iiodev->num_channels = ARRAY_SIZE(ep93xx_adc_channels);
	iiodev->channels = ep93xx_adc_channels;

	priv->lastch = -1;
	mutex_init(&priv->lock);

	platform_set_drvdata(pdev, iiodev);

	priv->clk = devm_clk_get(&pdev->dev, NULL);
	if (IS_ERR(priv->clk)) {
		dev_err(&pdev->dev, "Cannot obtain clock\n");
		return PTR_ERR(priv->clk);
	}

	pclk = clk_get_parent(priv->clk);
	if (!pclk) {
		dev_warn(&pdev->dev, "Cannot obtain parent clock\n");
	} else {
		/*
		 * This is actually a place for improvement:
		 * EP93xx ADC supports two clock divisors -- 4 and 16,
		 * resulting in conversion rates 3750 and 925 samples per second
		 * with 500us or 2ms settling time respectively.
		 * One might find this interesting enough to be configurable.
		 */
		ret = clk_set_rate(priv->clk, clk_get_rate(pclk) / 16);
		if (ret)
			dev_warn(&pdev->dev, "Cannot set clock rate\n");
		/*
		 * We can tolerate rate setting failure because the module should
		 * work in any case.
		 */
	}

	ret = clk_enable(priv->clk);
	if (ret) {
		dev_err(&pdev->dev, "Cannot enable clock\n");
		return ret;
	}

	ret = iio_device_register(iiodev);
	if (ret)
		clk_disable(priv->clk);

	return ret;
}