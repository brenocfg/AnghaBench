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
struct device {int dummy; } ;
struct platform_device {struct device dev; } ;
struct TYPE_2__ {struct device* parent; } ;
struct iio_dev {int num_channels; int /*<<< orphan*/ * channels; int /*<<< orphan*/  modes; int /*<<< orphan*/ * info; TYPE_1__ dev; int /*<<< orphan*/  name; } ;
struct dpot_dac {int max_ohms; int /*<<< orphan*/  vref; int /*<<< orphan*/  dpot; } ;
typedef  enum iio_chan_type { ____Placeholder_iio_chan_type } iio_chan_type ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int EPROBE_DEFER ; 
 int IIO_RESISTANCE ; 
 int /*<<< orphan*/  INDIO_DIRECT_MODE ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 int /*<<< orphan*/  dev_name (struct device*) ; 
 int /*<<< orphan*/  devm_iio_channel_get (struct device*,char*) ; 
 struct iio_dev* devm_iio_device_alloc (struct device*,int) ; 
 int /*<<< orphan*/  devm_regulator_get (struct device*,char*) ; 
 int dpot_dac_channel_max_ohms (struct iio_dev*) ; 
 int /*<<< orphan*/  dpot_dac_iio_channel ; 
 int /*<<< orphan*/  dpot_dac_info ; 
 int iio_device_register (struct iio_dev*) ; 
 int iio_get_channel_type (int /*<<< orphan*/ ,int*) ; 
 struct dpot_dac* iio_priv (struct iio_dev*) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct iio_dev*) ; 
 int /*<<< orphan*/  regulator_disable (int /*<<< orphan*/ ) ; 
 int regulator_enable (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int dpot_dac_probe(struct platform_device *pdev)
{
	struct device *dev = &pdev->dev;
	struct iio_dev *indio_dev;
	struct dpot_dac *dac;
	enum iio_chan_type type;
	int ret;

	indio_dev = devm_iio_device_alloc(dev, sizeof(*dac));
	if (!indio_dev)
		return -ENOMEM;

	platform_set_drvdata(pdev, indio_dev);
	dac = iio_priv(indio_dev);

	indio_dev->name = dev_name(dev);
	indio_dev->dev.parent = dev;
	indio_dev->info = &dpot_dac_info;
	indio_dev->modes = INDIO_DIRECT_MODE;
	indio_dev->channels = &dpot_dac_iio_channel;
	indio_dev->num_channels = 1;

	dac->vref = devm_regulator_get(dev, "vref");
	if (IS_ERR(dac->vref)) {
		if (PTR_ERR(dac->vref) != -EPROBE_DEFER)
			dev_err(&pdev->dev, "failed to get vref regulator\n");
		return PTR_ERR(dac->vref);
	}

	dac->dpot = devm_iio_channel_get(dev, "dpot");
	if (IS_ERR(dac->dpot)) {
		if (PTR_ERR(dac->dpot) != -EPROBE_DEFER)
			dev_err(dev, "failed to get dpot input channel\n");
		return PTR_ERR(dac->dpot);
	}

	ret = iio_get_channel_type(dac->dpot, &type);
	if (ret < 0)
		return ret;

	if (type != IIO_RESISTANCE) {
		dev_err(dev, "dpot is of the wrong type\n");
		return -EINVAL;
	}

	ret = dpot_dac_channel_max_ohms(indio_dev);
	if (ret < 0)
		return ret;
	dac->max_ohms = ret;

	ret = regulator_enable(dac->vref);
	if (ret) {
		dev_err(dev, "failed to enable the vref regulator\n");
		return ret;
	}

	ret = iio_device_register(indio_dev);
	if (ret) {
		dev_err(dev, "failed to register iio device\n");
		goto disable_reg;
	}

	return 0;

disable_reg:
	regulator_disable(dac->vref);
	return ret;
}