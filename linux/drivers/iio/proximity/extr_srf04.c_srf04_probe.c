#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct srf04_data {scalar_t__ irqnr; struct device* dev; void* gpiod_echo; void* gpiod_trig; int /*<<< orphan*/  falling; int /*<<< orphan*/  rising; int /*<<< orphan*/  lock; int /*<<< orphan*/  cfg; } ;
struct device {int dummy; } ;
struct platform_device {struct device dev; int /*<<< orphan*/  name; } ;
struct TYPE_3__ {struct device* parent; } ;
struct iio_dev {char* name; int /*<<< orphan*/  num_channels; int /*<<< orphan*/  channels; int /*<<< orphan*/  modes; int /*<<< orphan*/ * info; TYPE_1__ dev; } ;
struct TYPE_4__ {int /*<<< orphan*/  data; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GPIOD_IN ; 
 int /*<<< orphan*/  GPIOD_OUT_LOW ; 
 int /*<<< orphan*/  INDIO_DIRECT_MODE ; 
 int IRQF_TRIGGER_FALLING ; 
 int IRQF_TRIGGER_RISING ; 
 scalar_t__ IS_ERR (void*) ; 
 int PTR_ERR (void*) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,...) ; 
 void* devm_gpiod_get (struct device*,char*,int /*<<< orphan*/ ) ; 
 struct iio_dev* devm_iio_device_alloc (struct device*,int) ; 
 int devm_iio_device_register (struct device*,struct iio_dev*) ; 
 int devm_request_irq (struct device*,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,struct iio_dev*) ; 
 scalar_t__ gpiod_cansleep (void*) ; 
 scalar_t__ gpiod_to_irq (void*) ; 
 struct srf04_data* iio_priv (struct iio_dev*) ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 TYPE_2__* of_match_device (int /*<<< orphan*/ ,struct device*) ; 
 int /*<<< orphan*/  of_srf04_match ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct iio_dev*) ; 
 int /*<<< orphan*/  srf04_chan_spec ; 
 int /*<<< orphan*/  srf04_handle_irq ; 
 int /*<<< orphan*/  srf04_iio_info ; 

__attribute__((used)) static int srf04_probe(struct platform_device *pdev)
{
	struct device *dev = &pdev->dev;
	struct srf04_data *data;
	struct iio_dev *indio_dev;
	int ret;

	indio_dev = devm_iio_device_alloc(dev, sizeof(struct srf04_data));
	if (!indio_dev) {
		dev_err(dev, "failed to allocate IIO device\n");
		return -ENOMEM;
	}

	data = iio_priv(indio_dev);
	data->dev = dev;
	data->cfg = of_match_device(of_srf04_match, dev)->data;

	mutex_init(&data->lock);
	init_completion(&data->rising);
	init_completion(&data->falling);

	data->gpiod_trig = devm_gpiod_get(dev, "trig", GPIOD_OUT_LOW);
	if (IS_ERR(data->gpiod_trig)) {
		dev_err(dev, "failed to get trig-gpios: err=%ld\n",
					PTR_ERR(data->gpiod_trig));
		return PTR_ERR(data->gpiod_trig);
	}

	data->gpiod_echo = devm_gpiod_get(dev, "echo", GPIOD_IN);
	if (IS_ERR(data->gpiod_echo)) {
		dev_err(dev, "failed to get echo-gpios: err=%ld\n",
					PTR_ERR(data->gpiod_echo));
		return PTR_ERR(data->gpiod_echo);
	}

	if (gpiod_cansleep(data->gpiod_echo)) {
		dev_err(data->dev, "cansleep-GPIOs not supported\n");
		return -ENODEV;
	}

	data->irqnr = gpiod_to_irq(data->gpiod_echo);
	if (data->irqnr < 0) {
		dev_err(data->dev, "gpiod_to_irq: %d\n", data->irqnr);
		return data->irqnr;
	}

	ret = devm_request_irq(dev, data->irqnr, srf04_handle_irq,
			IRQF_TRIGGER_RISING | IRQF_TRIGGER_FALLING,
			pdev->name, indio_dev);
	if (ret < 0) {
		dev_err(data->dev, "request_irq: %d\n", ret);
		return ret;
	}

	platform_set_drvdata(pdev, indio_dev);

	indio_dev->name = "srf04";
	indio_dev->dev.parent = &pdev->dev;
	indio_dev->info = &srf04_iio_info;
	indio_dev->modes = INDIO_DIRECT_MODE;
	indio_dev->channels = srf04_chan_spec;
	indio_dev->num_channels = ARRAY_SIZE(srf04_chan_spec);

	return devm_iio_device_register(dev, indio_dev);
}