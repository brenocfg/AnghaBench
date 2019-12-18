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
struct platform_device {struct device dev; int /*<<< orphan*/  name; } ;
struct TYPE_2__ {struct device* parent; } ;
struct iio_dev {int /*<<< orphan*/  num_channels; int /*<<< orphan*/  channels; int /*<<< orphan*/  modes; int /*<<< orphan*/ * info; TYPE_1__ dev; int /*<<< orphan*/  name; } ;
struct dht11 {scalar_t__ irq; int num_edges; int /*<<< orphan*/  lock; int /*<<< orphan*/  completion; scalar_t__ timestamp; int /*<<< orphan*/  gpiod; struct device* dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 scalar_t__ DHT11_DATA_VALID_TIME ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GPIOD_IN ; 
 int /*<<< orphan*/  INDIO_DIRECT_MODE ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  desc_to_gpio (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,...) ; 
 int /*<<< orphan*/  devm_gpiod_get (struct device*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct iio_dev* devm_iio_device_alloc (struct device*,int) ; 
 int devm_iio_device_register (struct device*,struct iio_dev*) ; 
 int /*<<< orphan*/  dht11_chan_spec ; 
 int /*<<< orphan*/  dht11_iio_info ; 
 scalar_t__ gpiod_to_irq (int /*<<< orphan*/ ) ; 
 struct dht11* iio_priv (struct iio_dev*) ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 scalar_t__ ktime_get_boottime_ns () ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct iio_dev*) ; 

__attribute__((used)) static int dht11_probe(struct platform_device *pdev)
{
	struct device *dev = &pdev->dev;
	struct dht11 *dht11;
	struct iio_dev *iio;

	iio = devm_iio_device_alloc(dev, sizeof(*dht11));
	if (!iio) {
		dev_err(dev, "Failed to allocate IIO device\n");
		return -ENOMEM;
	}

	dht11 = iio_priv(iio);
	dht11->dev = dev;
	dht11->gpiod = devm_gpiod_get(dev, NULL, GPIOD_IN);
	if (IS_ERR(dht11->gpiod))
		return PTR_ERR(dht11->gpiod);

	dht11->irq = gpiod_to_irq(dht11->gpiod);
	if (dht11->irq < 0) {
		dev_err(dev, "GPIO %d has no interrupt\n", desc_to_gpio(dht11->gpiod));
		return -EINVAL;
	}

	dht11->timestamp = ktime_get_boottime_ns() - DHT11_DATA_VALID_TIME - 1;
	dht11->num_edges = -1;

	platform_set_drvdata(pdev, iio);

	init_completion(&dht11->completion);
	mutex_init(&dht11->lock);
	iio->name = pdev->name;
	iio->dev.parent = &pdev->dev;
	iio->info = &dht11_iio_info;
	iio->modes = INDIO_DIRECT_MODE;
	iio->channels = dht11_chan_spec;
	iio->num_channels = ARRAY_SIZE(dht11_chan_spec);

	return devm_iio_device_register(dev, iio);
}