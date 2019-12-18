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
struct TYPE_2__ {struct device* parent; } ;
struct iio_dev {int /*<<< orphan*/  modes; int /*<<< orphan*/ * info; TYPE_1__ dev; } ;
struct device {int dummy; } ;
struct ade7854_state {int /*<<< orphan*/  buf_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  INDIO_DIRECT_MODE ; 
 int /*<<< orphan*/  ade7854_info ; 
 int ade7854_initial_setup (struct iio_dev*) ; 
 int devm_iio_device_register (struct device*,struct iio_dev*) ; 
 struct ade7854_state* iio_priv (struct iio_dev*) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 

int ade7854_probe(struct iio_dev *indio_dev, struct device *dev)
{
	int ret;
	struct ade7854_state *st = iio_priv(indio_dev);
	/* setup the industrialio driver allocated elements */
	mutex_init(&st->buf_lock);

	indio_dev->dev.parent = dev;
	indio_dev->info = &ade7854_info;
	indio_dev->modes = INDIO_DIRECT_MODE;

	ret = devm_iio_device_register(dev, indio_dev);
	if (ret)
		return ret;

	/* Get the device into a sane initial state */
	return ade7854_initial_setup(indio_dev);
}