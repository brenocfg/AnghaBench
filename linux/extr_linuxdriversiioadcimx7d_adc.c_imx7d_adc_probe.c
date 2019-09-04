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
struct imx7d_adc {int /*<<< orphan*/  vref; int /*<<< orphan*/  clk; int /*<<< orphan*/ * dev; int /*<<< orphan*/  completion; int /*<<< orphan*/  regs; } ;
struct TYPE_2__ {int /*<<< orphan*/ * parent; } ;
struct iio_dev {int /*<<< orphan*/  num_channels; int /*<<< orphan*/  channels; int /*<<< orphan*/  modes; int /*<<< orphan*/ * info; TYPE_1__ dev; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  INDIO_DIRECT_MODE ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int clk_prepare_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  dev_name (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  devm_clk_get (int /*<<< orphan*/ *,char*) ; 
 struct iio_dev* devm_iio_device_alloc (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  devm_ioremap_resource (int /*<<< orphan*/ *,struct resource*) ; 
 int /*<<< orphan*/  devm_regulator_get (int /*<<< orphan*/ *,char*) ; 
 int devm_request_irq (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct imx7d_adc*) ; 
 int iio_device_register (struct iio_dev*) ; 
 struct imx7d_adc* iio_priv (struct iio_dev*) ; 
 int /*<<< orphan*/  imx7d_adc_feature_config (struct imx7d_adc*) ; 
 int /*<<< orphan*/  imx7d_adc_hw_init (struct imx7d_adc*) ; 
 int /*<<< orphan*/  imx7d_adc_iio_channels ; 
 int /*<<< orphan*/  imx7d_adc_iio_info ; 
 int /*<<< orphan*/  imx7d_adc_isr ; 
 int /*<<< orphan*/  imx7d_adc_power_down (struct imx7d_adc*) ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 int platform_get_irq (struct platform_device*,int /*<<< orphan*/ ) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct iio_dev*) ; 
 int /*<<< orphan*/  regulator_disable (int /*<<< orphan*/ ) ; 
 int regulator_enable (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int imx7d_adc_probe(struct platform_device *pdev)
{
	struct imx7d_adc *info;
	struct iio_dev *indio_dev;
	struct resource *mem;
	int irq;
	int ret;

	indio_dev = devm_iio_device_alloc(&pdev->dev, sizeof(*info));
	if (!indio_dev) {
		dev_err(&pdev->dev, "Failed allocating iio device\n");
		return -ENOMEM;
	}

	info = iio_priv(indio_dev);
	info->dev = &pdev->dev;

	mem = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	info->regs = devm_ioremap_resource(&pdev->dev, mem);
	if (IS_ERR(info->regs)) {
		ret = PTR_ERR(info->regs);
		dev_err(&pdev->dev,
			"Failed to remap adc memory, err = %d\n", ret);
		return ret;
	}

	irq = platform_get_irq(pdev, 0);
	if (irq < 0) {
		dev_err(&pdev->dev, "No irq resource?\n");
		return irq;
	}

	info->clk = devm_clk_get(&pdev->dev, "adc");
	if (IS_ERR(info->clk)) {
		ret = PTR_ERR(info->clk);
		dev_err(&pdev->dev, "Failed getting clock, err = %d\n", ret);
		return ret;
	}

	info->vref = devm_regulator_get(&pdev->dev, "vref");
	if (IS_ERR(info->vref)) {
		ret = PTR_ERR(info->vref);
		dev_err(&pdev->dev,
			"Failed getting reference voltage, err = %d\n", ret);
		return ret;
	}

	ret = regulator_enable(info->vref);
	if (ret) {
		dev_err(&pdev->dev,
			"Can't enable adc reference top voltage, err = %d\n",
			ret);
		return ret;
	}

	platform_set_drvdata(pdev, indio_dev);

	init_completion(&info->completion);

	indio_dev->name = dev_name(&pdev->dev);
	indio_dev->dev.parent = &pdev->dev;
	indio_dev->info = &imx7d_adc_iio_info;
	indio_dev->modes = INDIO_DIRECT_MODE;
	indio_dev->channels = imx7d_adc_iio_channels;
	indio_dev->num_channels = ARRAY_SIZE(imx7d_adc_iio_channels);

	ret = clk_prepare_enable(info->clk);
	if (ret) {
		dev_err(&pdev->dev,
			"Could not prepare or enable the clock.\n");
		goto error_adc_clk_enable;
	}

	ret = devm_request_irq(info->dev, irq,
				imx7d_adc_isr, 0,
				dev_name(&pdev->dev), info);
	if (ret < 0) {
		dev_err(&pdev->dev, "Failed requesting irq, irq = %d\n", irq);
		goto error_iio_device_register;
	}

	imx7d_adc_feature_config(info);
	imx7d_adc_hw_init(info);

	ret = iio_device_register(indio_dev);
	if (ret) {
		imx7d_adc_power_down(info);
		dev_err(&pdev->dev, "Couldn't register the device.\n");
		goto error_iio_device_register;
	}

	return 0;

error_iio_device_register:
	clk_disable_unprepare(info->clk);
error_adc_clk_enable:
	regulator_disable(info->vref);

	return ret;
}