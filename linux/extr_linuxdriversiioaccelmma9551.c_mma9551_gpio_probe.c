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
struct mma9551_data {int* irqs; TYPE_1__* client; } ;
struct iio_dev {int dummy; } ;
struct gpio_desc {int dummy; } ;
struct device {int dummy; } ;
struct TYPE_2__ {struct device dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  GPIOD_IN ; 
 int IRQF_ONESHOT ; 
 int IRQF_TRIGGER_RISING ; 
 scalar_t__ IS_ERR (struct gpio_desc*) ; 
 int MMA9551_GPIO_COUNT ; 
 int /*<<< orphan*/  MMA9551_IRQ_NAME ; 
 int PTR_ERR (struct gpio_desc*) ; 
 int /*<<< orphan*/  desc_to_gpio (struct gpio_desc*) ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,...) ; 
 struct gpio_desc* devm_gpiod_get_index (struct device*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int devm_request_threaded_irq (struct device*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,struct iio_dev*) ; 
 int gpiod_to_irq (struct gpio_desc*) ; 
 struct mma9551_data* iio_priv (struct iio_dev*) ; 
 int /*<<< orphan*/  mma9551_event_handler ; 

__attribute__((used)) static int mma9551_gpio_probe(struct iio_dev *indio_dev)
{
	struct gpio_desc *gpio;
	int i, ret;
	struct mma9551_data *data = iio_priv(indio_dev);
	struct device *dev = &data->client->dev;

	for (i = 0; i < MMA9551_GPIO_COUNT; i++) {
		gpio = devm_gpiod_get_index(dev, NULL, i, GPIOD_IN);
		if (IS_ERR(gpio)) {
			dev_err(dev, "acpi gpio get index failed\n");
			return PTR_ERR(gpio);
		}

		ret = gpiod_to_irq(gpio);
		if (ret < 0)
			return ret;

		data->irqs[i] = ret;
		ret = devm_request_threaded_irq(dev, data->irqs[i],
				NULL, mma9551_event_handler,
				IRQF_TRIGGER_RISING | IRQF_ONESHOT,
				MMA9551_IRQ_NAME, indio_dev);
		if (ret < 0) {
			dev_err(dev, "request irq %d failed\n", data->irqs[i]);
			return ret;
		}

		dev_dbg(dev, "gpio resource, no:%d irq:%d\n",
			desc_to_gpio(gpio), data->irqs[i]);
	}

	return 0;
}