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
struct stm32_timer_trigger {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  of_node; struct device* parent; } ;
struct iio_dev {int num_channels; TYPE_1__ dev; int /*<<< orphan*/ * channels; int /*<<< orphan*/  modes; int /*<<< orphan*/ * info; int /*<<< orphan*/  name; } ;
struct device {int /*<<< orphan*/  of_node; } ;

/* Variables and functions */
 int /*<<< orphan*/  INDIO_HARDWARE_TRIGGERED ; 
 int /*<<< orphan*/  dev_name (struct device*) ; 
 struct iio_dev* devm_iio_device_alloc (struct device*,int) ; 
 int devm_iio_device_register (struct device*,struct iio_dev*) ; 
 struct stm32_timer_trigger* iio_priv (struct iio_dev*) ; 
 int /*<<< orphan*/  stm32_trigger_channel ; 
 int /*<<< orphan*/  stm32_trigger_info ; 

__attribute__((used)) static struct stm32_timer_trigger *stm32_setup_counter_device(struct device *dev)
{
	struct iio_dev *indio_dev;
	int ret;

	indio_dev = devm_iio_device_alloc(dev,
					  sizeof(struct stm32_timer_trigger));
	if (!indio_dev)
		return NULL;

	indio_dev->name = dev_name(dev);
	indio_dev->dev.parent = dev;
	indio_dev->info = &stm32_trigger_info;
	indio_dev->modes = INDIO_HARDWARE_TRIGGERED;
	indio_dev->num_channels = 1;
	indio_dev->channels = &stm32_trigger_channel;
	indio_dev->dev.of_node = dev->of_node;

	ret = devm_iio_device_register(dev, indio_dev);
	if (ret)
		return NULL;

	return iio_priv(indio_dev);
}