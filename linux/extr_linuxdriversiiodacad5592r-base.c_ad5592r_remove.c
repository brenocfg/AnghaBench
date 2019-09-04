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
struct ad5592r_state {scalar_t__ reg; } ;

/* Variables and functions */
 int /*<<< orphan*/  ad5592r_gpio_cleanup (struct ad5592r_state*) ; 
 int /*<<< orphan*/  ad5592r_reset_channel_modes (struct ad5592r_state*) ; 
 struct iio_dev* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  iio_device_unregister (struct iio_dev*) ; 
 struct ad5592r_state* iio_priv (struct iio_dev*) ; 
 int /*<<< orphan*/  regulator_disable (scalar_t__) ; 

int ad5592r_remove(struct device *dev)
{
	struct iio_dev *iio_dev = dev_get_drvdata(dev);
	struct ad5592r_state *st = iio_priv(iio_dev);

	iio_device_unregister(iio_dev);
	ad5592r_reset_channel_modes(st);
	ad5592r_gpio_cleanup(st);

	if (st->reg)
		regulator_disable(st->reg);

	return 0;
}