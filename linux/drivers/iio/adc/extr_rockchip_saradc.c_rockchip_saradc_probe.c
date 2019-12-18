#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
struct rockchip_saradc {int /*<<< orphan*/ * vref; int /*<<< orphan*/ * pclk; int /*<<< orphan*/ * clk; TYPE_2__* data; int /*<<< orphan*/ * reset; int /*<<< orphan*/  completion; int /*<<< orphan*/ * regs; } ;
struct resource {int dummy; } ;
struct TYPE_15__ {struct device_node* of_node; } ;
struct platform_device {TYPE_3__ dev; } ;
struct of_device_id {TYPE_2__* data; } ;
struct TYPE_13__ {struct device_node* of_node; TYPE_3__* parent; } ;
struct iio_dev {int /*<<< orphan*/  num_channels; int /*<<< orphan*/  channels; int /*<<< orphan*/  modes; int /*<<< orphan*/ * info; TYPE_1__ dev; int /*<<< orphan*/  name; } ;
struct device_node {int dummy; } ;
struct TYPE_14__ {int /*<<< orphan*/  num_channels; int /*<<< orphan*/  channels; int /*<<< orphan*/  clk_rate; } ;

/* Variables and functions */
 int ENODEV ; 
 int ENOENT ; 
 int ENOMEM ; 
 int /*<<< orphan*/  INDIO_DIRECT_MODE ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ *) ; 
 int PTR_ERR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ *) ; 
 int clk_prepare_enable (int /*<<< orphan*/ *) ; 
 int clk_set_rate (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_dbg (TYPE_3__*,char*) ; 
 int /*<<< orphan*/  dev_err (TYPE_3__*,char*,...) ; 
 int /*<<< orphan*/  dev_name (TYPE_3__*) ; 
 void* devm_clk_get (TYPE_3__*,char*) ; 
 struct iio_dev* devm_iio_device_alloc (TYPE_3__*,int) ; 
 int /*<<< orphan*/ * devm_ioremap_resource (TYPE_3__*,struct resource*) ; 
 int /*<<< orphan*/ * devm_regulator_get (TYPE_3__*,char*) ; 
 int devm_request_irq (TYPE_3__*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct rockchip_saradc*) ; 
 int /*<<< orphan*/ * devm_reset_control_get_exclusive (TYPE_3__*,char*) ; 
 int iio_device_register (struct iio_dev*) ; 
 struct rockchip_saradc* iio_priv (struct iio_dev*) ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 struct of_device_id* of_match_device (int /*<<< orphan*/ ,TYPE_3__*) ; 
 int platform_get_irq (struct platform_device*,int /*<<< orphan*/ ) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct iio_dev*) ; 
 int /*<<< orphan*/  regulator_disable (int /*<<< orphan*/ *) ; 
 int regulator_enable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rockchip_saradc_iio_info ; 
 int /*<<< orphan*/  rockchip_saradc_isr ; 
 int /*<<< orphan*/  rockchip_saradc_match ; 
 int /*<<< orphan*/  rockchip_saradc_reset_controller (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int rockchip_saradc_probe(struct platform_device *pdev)
{
	struct rockchip_saradc *info = NULL;
	struct device_node *np = pdev->dev.of_node;
	struct iio_dev *indio_dev = NULL;
	struct resource	*mem;
	const struct of_device_id *match;
	int ret;
	int irq;

	if (!np)
		return -ENODEV;

	indio_dev = devm_iio_device_alloc(&pdev->dev, sizeof(*info));
	if (!indio_dev) {
		dev_err(&pdev->dev, "failed allocating iio device\n");
		return -ENOMEM;
	}
	info = iio_priv(indio_dev);

	match = of_match_device(rockchip_saradc_match, &pdev->dev);
	if (!match) {
		dev_err(&pdev->dev, "failed to match device\n");
		return -ENODEV;
	}

	info->data = match->data;

	mem = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	info->regs = devm_ioremap_resource(&pdev->dev, mem);
	if (IS_ERR(info->regs))
		return PTR_ERR(info->regs);

	/*
	 * The reset should be an optional property, as it should work
	 * with old devicetrees as well
	 */
	info->reset = devm_reset_control_get_exclusive(&pdev->dev,
						       "saradc-apb");
	if (IS_ERR(info->reset)) {
		ret = PTR_ERR(info->reset);
		if (ret != -ENOENT)
			return ret;

		dev_dbg(&pdev->dev, "no reset control found\n");
		info->reset = NULL;
	}

	init_completion(&info->completion);

	irq = platform_get_irq(pdev, 0);
	if (irq < 0)
		return irq;

	ret = devm_request_irq(&pdev->dev, irq, rockchip_saradc_isr,
			       0, dev_name(&pdev->dev), info);
	if (ret < 0) {
		dev_err(&pdev->dev, "failed requesting irq %d\n", irq);
		return ret;
	}

	info->pclk = devm_clk_get(&pdev->dev, "apb_pclk");
	if (IS_ERR(info->pclk)) {
		dev_err(&pdev->dev, "failed to get pclk\n");
		return PTR_ERR(info->pclk);
	}

	info->clk = devm_clk_get(&pdev->dev, "saradc");
	if (IS_ERR(info->clk)) {
		dev_err(&pdev->dev, "failed to get adc clock\n");
		return PTR_ERR(info->clk);
	}

	info->vref = devm_regulator_get(&pdev->dev, "vref");
	if (IS_ERR(info->vref)) {
		dev_err(&pdev->dev, "failed to get regulator, %ld\n",
			PTR_ERR(info->vref));
		return PTR_ERR(info->vref);
	}

	if (info->reset)
		rockchip_saradc_reset_controller(info->reset);

	/*
	 * Use a default value for the converter clock.
	 * This may become user-configurable in the future.
	 */
	ret = clk_set_rate(info->clk, info->data->clk_rate);
	if (ret < 0) {
		dev_err(&pdev->dev, "failed to set adc clk rate, %d\n", ret);
		return ret;
	}

	ret = regulator_enable(info->vref);
	if (ret < 0) {
		dev_err(&pdev->dev, "failed to enable vref regulator\n");
		return ret;
	}

	ret = clk_prepare_enable(info->pclk);
	if (ret < 0) {
		dev_err(&pdev->dev, "failed to enable pclk\n");
		goto err_reg_voltage;
	}

	ret = clk_prepare_enable(info->clk);
	if (ret < 0) {
		dev_err(&pdev->dev, "failed to enable converter clock\n");
		goto err_pclk;
	}

	platform_set_drvdata(pdev, indio_dev);

	indio_dev->name = dev_name(&pdev->dev);
	indio_dev->dev.parent = &pdev->dev;
	indio_dev->dev.of_node = pdev->dev.of_node;
	indio_dev->info = &rockchip_saradc_iio_info;
	indio_dev->modes = INDIO_DIRECT_MODE;

	indio_dev->channels = info->data->channels;
	indio_dev->num_channels = info->data->num_channels;

	ret = iio_device_register(indio_dev);
	if (ret)
		goto err_clk;

	return 0;

err_clk:
	clk_disable_unprepare(info->clk);
err_pclk:
	clk_disable_unprepare(info->pclk);
err_reg_voltage:
	regulator_disable(info->vref);
	return ret;
}