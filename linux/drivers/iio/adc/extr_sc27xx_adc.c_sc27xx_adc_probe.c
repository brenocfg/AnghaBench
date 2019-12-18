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
struct sc27xx_adc_data {scalar_t__ irq; struct device* dev; struct sc27xx_adc_data* hwlock; int /*<<< orphan*/  base; int /*<<< orphan*/  regmap; } ;
struct device {int /*<<< orphan*/  parent; struct device_node* of_node; } ;
struct platform_device {struct device dev; } ;
struct TYPE_2__ {struct device* parent; } ;
struct iio_dev {int /*<<< orphan*/  num_channels; int /*<<< orphan*/  channels; int /*<<< orphan*/ * info; int /*<<< orphan*/  modes; int /*<<< orphan*/  name; TYPE_1__ dev; } ;
struct device_node {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int ENODEV ; 
 int ENOMEM ; 
 int ENXIO ; 
 int /*<<< orphan*/  INDIO_DIRECT_MODE ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 int /*<<< orphan*/  dev_get_regmap (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_name (struct device*) ; 
 int devm_add_action_or_reset (struct device*,int /*<<< orphan*/ ,struct sc27xx_adc_data*) ; 
 struct iio_dev* devm_iio_device_alloc (struct device*,int) ; 
 int devm_iio_device_register (struct device*,struct iio_dev*) ; 
 struct sc27xx_adc_data* hwspin_lock_request_specific (int) ; 
 struct sc27xx_adc_data* iio_priv (struct iio_dev*) ; 
 int of_hwspin_lock_get_id (struct device_node*,int /*<<< orphan*/ ) ; 
 int of_property_read_u32 (struct device_node*,char*,int /*<<< orphan*/ *) ; 
 scalar_t__ platform_get_irq (struct platform_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sc27xx_adc_disable ; 
 int sc27xx_adc_enable (struct sc27xx_adc_data*) ; 
 int /*<<< orphan*/  sc27xx_adc_free_hwlock ; 
 int /*<<< orphan*/  sc27xx_channels ; 
 int /*<<< orphan*/  sc27xx_info ; 

__attribute__((used)) static int sc27xx_adc_probe(struct platform_device *pdev)
{
	struct device *dev = &pdev->dev;
	struct device_node *np = dev->of_node;
	struct sc27xx_adc_data *sc27xx_data;
	struct iio_dev *indio_dev;
	int ret;

	indio_dev = devm_iio_device_alloc(dev, sizeof(*sc27xx_data));
	if (!indio_dev)
		return -ENOMEM;

	sc27xx_data = iio_priv(indio_dev);

	sc27xx_data->regmap = dev_get_regmap(dev->parent, NULL);
	if (!sc27xx_data->regmap) {
		dev_err(dev, "failed to get ADC regmap\n");
		return -ENODEV;
	}

	ret = of_property_read_u32(np, "reg", &sc27xx_data->base);
	if (ret) {
		dev_err(dev, "failed to get ADC base address\n");
		return ret;
	}

	sc27xx_data->irq = platform_get_irq(pdev, 0);
	if (sc27xx_data->irq < 0)
		return sc27xx_data->irq;

	ret = of_hwspin_lock_get_id(np, 0);
	if (ret < 0) {
		dev_err(dev, "failed to get hwspinlock id\n");
		return ret;
	}

	sc27xx_data->hwlock = hwspin_lock_request_specific(ret);
	if (!sc27xx_data->hwlock) {
		dev_err(dev, "failed to request hwspinlock\n");
		return -ENXIO;
	}

	ret = devm_add_action_or_reset(dev, sc27xx_adc_free_hwlock,
			      sc27xx_data->hwlock);
	if (ret) {
		dev_err(dev, "failed to add hwspinlock action\n");
		return ret;
	}

	sc27xx_data->dev = dev;

	ret = sc27xx_adc_enable(sc27xx_data);
	if (ret) {
		dev_err(dev, "failed to enable ADC module\n");
		return ret;
	}

	ret = devm_add_action_or_reset(dev, sc27xx_adc_disable, sc27xx_data);
	if (ret) {
		dev_err(dev, "failed to add ADC disable action\n");
		return ret;
	}

	indio_dev->dev.parent = dev;
	indio_dev->name = dev_name(dev);
	indio_dev->modes = INDIO_DIRECT_MODE;
	indio_dev->info = &sc27xx_info;
	indio_dev->channels = sc27xx_channels;
	indio_dev->num_channels = ARRAY_SIZE(sc27xx_channels);
	ret = devm_iio_device_register(dev, indio_dev);
	if (ret)
		dev_err(dev, "could not register iio (ADC)");

	return ret;
}