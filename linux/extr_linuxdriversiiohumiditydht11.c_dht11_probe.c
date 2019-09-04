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
struct device {struct device_node* of_node; } ;
struct platform_device {struct device dev; int /*<<< orphan*/  name; } ;
struct TYPE_2__ {struct device* parent; } ;
struct iio_dev {int /*<<< orphan*/  num_channels; int /*<<< orphan*/  channels; int /*<<< orphan*/  modes; int /*<<< orphan*/ * info; TYPE_1__ dev; int /*<<< orphan*/  name; } ;
struct dht11 {int gpio; scalar_t__ irq; int num_edges; int /*<<< orphan*/  lock; int /*<<< orphan*/  completion; scalar_t__ timestamp; struct device* dev; } ;
struct device_node {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 scalar_t__ DHT11_DATA_VALID_TIME ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GPIOF_IN ; 
 int /*<<< orphan*/  INDIO_DIRECT_MODE ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,...) ; 
 int devm_gpio_request_one (struct device*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct iio_dev* devm_iio_device_alloc (struct device*,int) ; 
 int devm_iio_device_register (struct device*,struct iio_dev*) ; 
 int /*<<< orphan*/  dht11_chan_spec ; 
 int /*<<< orphan*/  dht11_iio_info ; 
 scalar_t__ gpio_to_irq (int) ; 
 struct dht11* iio_priv (struct iio_dev*) ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 scalar_t__ ktime_get_boot_ns () ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int of_get_gpio (struct device_node*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct iio_dev*) ; 

__attribute__((used)) static int dht11_probe(struct platform_device *pdev)
{
	struct device *dev = &pdev->dev;
	struct device_node *node = dev->of_node;
	struct dht11 *dht11;
	struct iio_dev *iio;
	int ret;

	iio = devm_iio_device_alloc(dev, sizeof(*dht11));
	if (!iio) {
		dev_err(dev, "Failed to allocate IIO device\n");
		return -ENOMEM;
	}

	dht11 = iio_priv(iio);
	dht11->dev = dev;

	ret = of_get_gpio(node, 0);
	if (ret < 0)
		return ret;
	dht11->gpio = ret;
	ret = devm_gpio_request_one(dev, dht11->gpio, GPIOF_IN, pdev->name);
	if (ret)
		return ret;

	dht11->irq = gpio_to_irq(dht11->gpio);
	if (dht11->irq < 0) {
		dev_err(dev, "GPIO %d has no interrupt\n", dht11->gpio);
		return -EINVAL;
	}

	dht11->timestamp = ktime_get_boot_ns() - DHT11_DATA_VALID_TIME - 1;
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