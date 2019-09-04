#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct iio_dev {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  HMC5843_MODE_SLEEP ; 
 struct iio_dev* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  hmc5843_set_mode (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iio_device_unregister (struct iio_dev*) ; 
 int /*<<< orphan*/  iio_priv (struct iio_dev*) ; 
 int /*<<< orphan*/  iio_triggered_buffer_cleanup (struct iio_dev*) ; 

int hmc5843_common_remove(struct device *dev)
{
	struct iio_dev *indio_dev = dev_get_drvdata(dev);

	iio_device_unregister(indio_dev);
	iio_triggered_buffer_cleanup(indio_dev);

	/*  sleep mode to save power */
	hmc5843_set_mode(iio_priv(indio_dev), HMC5843_MODE_SLEEP);

	return 0;
}