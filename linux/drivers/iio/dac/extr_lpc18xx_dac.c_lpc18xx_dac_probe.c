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
struct lpc18xx_dac {scalar_t__ vref; scalar_t__ clk; scalar_t__ base; int /*<<< orphan*/  lock; } ;
struct TYPE_2__ {int /*<<< orphan*/ * parent; } ;
struct iio_dev {int /*<<< orphan*/  num_channels; int /*<<< orphan*/  channels; int /*<<< orphan*/  modes; int /*<<< orphan*/ * info; TYPE_1__ dev; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  INDIO_DIRECT_MODE ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 scalar_t__ IS_ERR (scalar_t__) ; 
 scalar_t__ LPC18XX_DAC_CR ; 
 scalar_t__ LPC18XX_DAC_CTRL ; 
 int PTR_ERR (scalar_t__) ; 
 int /*<<< orphan*/  clk_disable_unprepare (scalar_t__) ; 
 int clk_prepare_enable (scalar_t__) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  dev_name (int /*<<< orphan*/ *) ; 
 scalar_t__ devm_clk_get (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct iio_dev* devm_iio_device_alloc (int /*<<< orphan*/ *,int) ; 
 scalar_t__ devm_ioremap_resource (int /*<<< orphan*/ *,struct resource*) ; 
 scalar_t__ devm_regulator_get (int /*<<< orphan*/ *,char*) ; 
 int iio_device_register (struct iio_dev*) ; 
 struct lpc18xx_dac* iio_priv (struct iio_dev*) ; 
 int /*<<< orphan*/  lpc18xx_dac_iio_channels ; 
 int /*<<< orphan*/  lpc18xx_dac_info ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct iio_dev*) ; 
 int /*<<< orphan*/  regulator_disable (scalar_t__) ; 
 int regulator_enable (scalar_t__) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int lpc18xx_dac_probe(struct platform_device *pdev)
{
	struct iio_dev *indio_dev;
	struct lpc18xx_dac *dac;
	struct resource *res;
	int ret;

	indio_dev = devm_iio_device_alloc(&pdev->dev, sizeof(*dac));
	if (!indio_dev)
		return -ENOMEM;

	platform_set_drvdata(pdev, indio_dev);
	dac = iio_priv(indio_dev);
	mutex_init(&dac->lock);

	res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	dac->base = devm_ioremap_resource(&pdev->dev, res);
	if (IS_ERR(dac->base))
		return PTR_ERR(dac->base);

	dac->clk = devm_clk_get(&pdev->dev, NULL);
	if (IS_ERR(dac->clk)) {
		dev_err(&pdev->dev, "error getting clock\n");
		return PTR_ERR(dac->clk);
	}

	dac->vref = devm_regulator_get(&pdev->dev, "vref");
	if (IS_ERR(dac->vref)) {
		dev_err(&pdev->dev, "error getting regulator\n");
		return PTR_ERR(dac->vref);
	}

	indio_dev->name = dev_name(&pdev->dev);
	indio_dev->dev.parent = &pdev->dev;
	indio_dev->info = &lpc18xx_dac_info;
	indio_dev->modes = INDIO_DIRECT_MODE;
	indio_dev->channels = lpc18xx_dac_iio_channels;
	indio_dev->num_channels = ARRAY_SIZE(lpc18xx_dac_iio_channels);

	ret = regulator_enable(dac->vref);
	if (ret) {
		dev_err(&pdev->dev, "unable to enable regulator\n");
		return ret;
	}

	ret = clk_prepare_enable(dac->clk);
	if (ret) {
		dev_err(&pdev->dev, "unable to enable clock\n");
		goto dis_reg;
	}

	writel(0, dac->base + LPC18XX_DAC_CTRL);
	writel(0, dac->base + LPC18XX_DAC_CR);

	ret = iio_device_register(indio_dev);
	if (ret) {
		dev_err(&pdev->dev, "unable to register device\n");
		goto dis_clk;
	}

	return 0;

dis_clk:
	clk_disable_unprepare(dac->clk);
dis_reg:
	regulator_disable(dac->vref);
	return ret;
}