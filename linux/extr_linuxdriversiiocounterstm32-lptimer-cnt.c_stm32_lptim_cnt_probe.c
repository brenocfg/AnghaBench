#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct stm32_lptimer {scalar_t__ has_encoder; int /*<<< orphan*/  clk; int /*<<< orphan*/  regmap; } ;
struct stm32_lptim_cnt {int /*<<< orphan*/  preset; int /*<<< orphan*/  clk; int /*<<< orphan*/  regmap; TYPE_2__* dev; } ;
struct TYPE_6__ {int /*<<< orphan*/  of_node; int /*<<< orphan*/  parent; } ;
struct platform_device {TYPE_2__ dev; } ;
struct TYPE_5__ {int /*<<< orphan*/  of_node; TYPE_2__* parent; } ;
struct iio_dev {int num_channels; int /*<<< orphan*/ * channels; int /*<<< orphan*/ * info; TYPE_1__ dev; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 scalar_t__ IS_ERR_OR_NULL (struct stm32_lptimer*) ; 
 int /*<<< orphan*/  STM32_LPTIM_MAX_ARR ; 
 struct stm32_lptimer* dev_get_drvdata (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_name (TYPE_2__*) ; 
 struct iio_dev* devm_iio_device_alloc (TYPE_2__*,int) ; 
 int devm_iio_device_register (TYPE_2__*,struct iio_dev*) ; 
 struct stm32_lptim_cnt* iio_priv (struct iio_dev*) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct stm32_lptim_cnt*) ; 
 int /*<<< orphan*/  stm32_lptim_cnt_channels ; 
 int /*<<< orphan*/  stm32_lptim_cnt_iio_info ; 
 int /*<<< orphan*/  stm32_lptim_enc_channels ; 

__attribute__((used)) static int stm32_lptim_cnt_probe(struct platform_device *pdev)
{
	struct stm32_lptimer *ddata = dev_get_drvdata(pdev->dev.parent);
	struct stm32_lptim_cnt *priv;
	struct iio_dev *indio_dev;

	if (IS_ERR_OR_NULL(ddata))
		return -EINVAL;

	indio_dev = devm_iio_device_alloc(&pdev->dev, sizeof(*priv));
	if (!indio_dev)
		return -ENOMEM;

	priv = iio_priv(indio_dev);
	priv->dev = &pdev->dev;
	priv->regmap = ddata->regmap;
	priv->clk = ddata->clk;
	priv->preset = STM32_LPTIM_MAX_ARR;

	indio_dev->name = dev_name(&pdev->dev);
	indio_dev->dev.parent = &pdev->dev;
	indio_dev->dev.of_node = pdev->dev.of_node;
	indio_dev->info = &stm32_lptim_cnt_iio_info;
	if (ddata->has_encoder)
		indio_dev->channels = &stm32_lptim_enc_channels;
	else
		indio_dev->channels = &stm32_lptim_cnt_channels;
	indio_dev->num_channels = 1;

	platform_set_drvdata(pdev, priv);

	return devm_iio_device_register(&pdev->dev, indio_dev);
}