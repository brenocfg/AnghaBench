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
struct platform_device_id {int /*<<< orphan*/  name; scalar_t__ driver_data; } ;
struct device {int /*<<< orphan*/  of_node; int /*<<< orphan*/  parent; } ;
struct platform_device {struct device dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  of_node; struct device* parent; } ;
struct iio_dev {int /*<<< orphan*/  channels; int /*<<< orphan*/  num_channels; int /*<<< orphan*/  info; int /*<<< orphan*/  name; int /*<<< orphan*/  modes; TYPE_1__ dev; } ;
struct axp_data {scalar_t__ adc_en2; int /*<<< orphan*/  maps; int /*<<< orphan*/  (* adc_rate ) (struct axp20x_adc_iio*,int) ;int /*<<< orphan*/  adc_en1_mask; int /*<<< orphan*/  channels; int /*<<< orphan*/  num_channels; int /*<<< orphan*/  iio_info; } ;
struct axp20x_dev {int /*<<< orphan*/  regmap; } ;
struct axp20x_adc_iio {int /*<<< orphan*/  regmap; struct axp_data* data; } ;

/* Variables and functions */
 int /*<<< orphan*/  AXP20X_ADC_EN1 ; 
 int /*<<< orphan*/  AXP20X_ADC_EN2 ; 
 int /*<<< orphan*/  AXP20X_ADC_EN2_MASK ; 
 int ENOMEM ; 
 int /*<<< orphan*/  INDIO_DIRECT_MODE ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,...) ; 
 struct axp20x_dev* dev_get_drvdata (int /*<<< orphan*/ ) ; 
 struct iio_dev* devm_iio_device_alloc (struct device*,int) ; 
 int iio_device_register (struct iio_dev*) ; 
 int iio_map_array_register (struct iio_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iio_map_array_unregister (struct iio_dev*) ; 
 struct axp20x_adc_iio* iio_priv (struct iio_dev*) ; 
 scalar_t__ of_device_get_match_data (struct device*) ; 
 struct platform_device_id* platform_get_device_id (struct platform_device*) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct iio_dev*) ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct axp20x_adc_iio*,int) ; 

__attribute__((used)) static int axp20x_probe(struct platform_device *pdev)
{
	struct axp20x_adc_iio *info;
	struct iio_dev *indio_dev;
	struct axp20x_dev *axp20x_dev;
	int ret;

	axp20x_dev = dev_get_drvdata(pdev->dev.parent);

	indio_dev = devm_iio_device_alloc(&pdev->dev, sizeof(*info));
	if (!indio_dev)
		return -ENOMEM;

	info = iio_priv(indio_dev);
	platform_set_drvdata(pdev, indio_dev);

	info->regmap = axp20x_dev->regmap;
	indio_dev->dev.parent = &pdev->dev;
	indio_dev->dev.of_node = pdev->dev.of_node;
	indio_dev->modes = INDIO_DIRECT_MODE;

	if (!pdev->dev.of_node) {
		const struct platform_device_id *id;

		id = platform_get_device_id(pdev);
		info->data = (struct axp_data *)id->driver_data;
	} else {
		struct device *dev = &pdev->dev;

		info->data = (struct axp_data *)of_device_get_match_data(dev);
	}

	indio_dev->name = platform_get_device_id(pdev)->name;
	indio_dev->info = info->data->iio_info;
	indio_dev->num_channels = info->data->num_channels;
	indio_dev->channels = info->data->channels;

	/* Enable the ADCs on IP */
	regmap_write(info->regmap, AXP20X_ADC_EN1, info->data->adc_en1_mask);

	if (info->data->adc_en2)
		/* Enable GPIO0/1 and internal temperature ADCs */
		regmap_update_bits(info->regmap, AXP20X_ADC_EN2,
				   AXP20X_ADC_EN2_MASK, AXP20X_ADC_EN2_MASK);

	/* Configure ADCs rate */
	info->data->adc_rate(info, 100);

	ret = iio_map_array_register(indio_dev, info->data->maps);
	if (ret < 0) {
		dev_err(&pdev->dev, "failed to register IIO maps: %d\n", ret);
		goto fail_map;
	}

	ret = iio_device_register(indio_dev);
	if (ret < 0) {
		dev_err(&pdev->dev, "could not register the device\n");
		goto fail_register;
	}

	return 0;

fail_register:
	iio_map_array_unregister(indio_dev);

fail_map:
	regmap_write(info->regmap, AXP20X_ADC_EN1, 0);

	if (info->data->adc_en2)
		regmap_write(info->regmap, AXP20X_ADC_EN2, 0);

	return ret;
}