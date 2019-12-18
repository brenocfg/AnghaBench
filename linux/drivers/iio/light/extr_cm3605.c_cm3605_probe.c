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
typedef  int u32 ;
struct device {struct device_node* of_node; } ;
struct platform_device {struct device dev; } ;
struct TYPE_2__ {struct device* parent; } ;
struct iio_dev {char* name; int /*<<< orphan*/  modes; int /*<<< orphan*/  num_channels; int /*<<< orphan*/  channels; int /*<<< orphan*/ * info; TYPE_1__ dev; } ;
struct device_node {int dummy; } ;
struct cm3605 {int als_max; int /*<<< orphan*/  vdd; int /*<<< orphan*/  aset; int /*<<< orphan*/  led; int /*<<< orphan*/  aout; int /*<<< orphan*/  dir; struct device* dev; } ;
typedef  enum iio_chan_type { ____Placeholder_iio_chan_type } iio_chan_type ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int EINVAL ; 
 int ENODEV ; 
 int ENOMEM ; 
 int EPROBE_DEFER ; 
 int /*<<< orphan*/  GPIOD_OUT_HIGH ; 
 int /*<<< orphan*/  IIO_EV_DIR_FALLING ; 
 int IIO_VOLTAGE ; 
 int /*<<< orphan*/  INDIO_DIRECT_MODE ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LED_FULL ; 
 int /*<<< orphan*/  LED_OFF ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cm3605_channels ; 
 int /*<<< orphan*/  cm3605_info ; 
 int /*<<< orphan*/  cm3605_prox_irq ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 int /*<<< orphan*/  dev_info (struct device*,char*,...) ; 
 int /*<<< orphan*/  devm_gpiod_get (struct device*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devm_iio_channel_get (struct device*,char*) ; 
 struct iio_dev* devm_iio_device_alloc (struct device*,int) ; 
 int /*<<< orphan*/  devm_regulator_get (struct device*,char*) ; 
 int devm_request_threaded_irq (struct device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,struct iio_dev*) ; 
 int /*<<< orphan*/  gpiod_set_value_cansleep (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int iio_device_register (struct iio_dev*) ; 
 int iio_get_channel_type (int /*<<< orphan*/ ,int*) ; 
 struct cm3605* iio_priv (struct iio_dev*) ; 
 int /*<<< orphan*/  led_trigger_event (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  led_trigger_register_simple (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  led_trigger_unregister_simple (int /*<<< orphan*/ ) ; 
 int of_property_read_u32 (struct device_node*,char*,int*) ; 
 int /*<<< orphan*/  platform_get_irq (struct platform_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct iio_dev*) ; 
 int /*<<< orphan*/  regulator_disable (int /*<<< orphan*/ ) ; 
 int regulator_enable (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int cm3605_probe(struct platform_device *pdev)
{
	struct cm3605 *cm3605;
	struct iio_dev *indio_dev;
	struct device *dev = &pdev->dev;
	struct device_node *np = dev->of_node;
	enum iio_chan_type ch_type;
	u32 rset;
	int ret;

	indio_dev = devm_iio_device_alloc(dev, sizeof(*cm3605));
	if (!indio_dev)
		return -ENOMEM;
	platform_set_drvdata(pdev, indio_dev);

	cm3605 = iio_priv(indio_dev);
	cm3605->dev = dev;
	cm3605->dir = IIO_EV_DIR_FALLING;

	ret = of_property_read_u32(np, "capella,aset-resistance-ohms", &rset);
	if (ret) {
		dev_info(dev, "no RSET specified, assuming 100K\n");
		rset = 100000;
	}
	switch (rset) {
	case 50000:
		cm3605->als_max = 650;
		break;
	case 100000:
		cm3605->als_max = 300;
		break;
	case 300000:
		cm3605->als_max = 100;
		break;
	case 600000:
		cm3605->als_max = 50;
		break;
	default:
		dev_info(dev, "non-standard resistance\n");
		return -EINVAL;
	}

	cm3605->aout = devm_iio_channel_get(dev, "aout");
	if (IS_ERR(cm3605->aout)) {
		if (PTR_ERR(cm3605->aout) == -ENODEV) {
			dev_err(dev, "no ADC, deferring...\n");
			return -EPROBE_DEFER;
		}
		dev_err(dev, "failed to get AOUT ADC channel\n");
		return PTR_ERR(cm3605->aout);
	}
	ret = iio_get_channel_type(cm3605->aout, &ch_type);
	if (ret < 0)
		return ret;
	if (ch_type != IIO_VOLTAGE) {
		dev_err(dev, "wrong type of IIO channel specified for AOUT\n");
		return -EINVAL;
	}

	cm3605->vdd = devm_regulator_get(dev, "vdd");
	if (IS_ERR(cm3605->vdd)) {
		dev_err(dev, "failed to get VDD regulator\n");
		return PTR_ERR(cm3605->vdd);
	}
	ret = regulator_enable(cm3605->vdd);
	if (ret) {
		dev_err(dev, "failed to enable VDD regulator\n");
		return ret;
	}

	cm3605->aset = devm_gpiod_get(dev, "aset", GPIOD_OUT_HIGH);
	if (IS_ERR(cm3605->aset)) {
		dev_err(dev, "no ASET GPIO\n");
		ret = PTR_ERR(cm3605->aset);
		goto out_disable_vdd;
	}

	ret = devm_request_threaded_irq(dev, platform_get_irq(pdev, 0),
			cm3605_prox_irq, NULL, 0, "cm3605", indio_dev);
	if (ret) {
		dev_err(dev, "unable to request IRQ\n");
		goto out_disable_aset;
	}

	/* Just name the trigger the same as the driver */
	led_trigger_register_simple("cm3605", &cm3605->led);
	led_trigger_event(cm3605->led, LED_FULL);

	indio_dev->dev.parent = dev;
	indio_dev->info = &cm3605_info;
	indio_dev->name = "cm3605";
	indio_dev->channels = cm3605_channels;
	indio_dev->num_channels = ARRAY_SIZE(cm3605_channels);
	indio_dev->modes = INDIO_DIRECT_MODE;

	ret = iio_device_register(indio_dev);
	if (ret)
		goto out_remove_trigger;
	dev_info(dev, "Capella Microsystems CM3605 enabled range 0..%d LUX\n",
		 cm3605->als_max);

	return 0;

out_remove_trigger:
	led_trigger_event(cm3605->led, LED_OFF);
	led_trigger_unregister_simple(cm3605->led);
out_disable_aset:
	gpiod_set_value_cansleep(cm3605->aset, 0);
out_disable_vdd:
	regulator_disable(cm3605->vdd);
	return ret;
}