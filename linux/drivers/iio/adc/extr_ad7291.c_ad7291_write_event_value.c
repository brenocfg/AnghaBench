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
struct iio_chan_spec {scalar_t__ type; } ;
struct ad7291_chip_info {int dummy; } ;
typedef  enum iio_event_type { ____Placeholder_iio_event_type } iio_event_type ;
typedef  enum iio_event_info { ____Placeholder_iio_event_info } iio_event_info ;
typedef  enum iio_event_direction { ____Placeholder_iio_event_direction } iio_event_direction ;

/* Variables and functions */
 int AD7291_VALUE_MASK ; 
 int EINVAL ; 
 int IIO_EV_INFO_HYSTERESIS ; 
 scalar_t__ IIO_VOLTAGE ; 
 int ad7291_i2c_write (struct ad7291_chip_info*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ad7291_threshold_reg (struct iio_chan_spec const*,int,int) ; 
 struct ad7291_chip_info* iio_priv (struct iio_dev*) ; 

__attribute__((used)) static int ad7291_write_event_value(struct iio_dev *indio_dev,
				    const struct iio_chan_spec *chan,
				    enum iio_event_type type,
				    enum iio_event_direction dir,
				    enum iio_event_info info,
				    int val, int val2)
{
	struct ad7291_chip_info *chip = iio_priv(indio_dev);

	if (info == IIO_EV_INFO_HYSTERESIS || chan->type == IIO_VOLTAGE) {
		if (val > AD7291_VALUE_MASK || val < 0)
			return -EINVAL;
	} else {
		if (val > 2047 || val < -2048)
			return -EINVAL;
	}

	return ad7291_i2c_write(chip, ad7291_threshold_reg(chan, dir, info),
				val);
}