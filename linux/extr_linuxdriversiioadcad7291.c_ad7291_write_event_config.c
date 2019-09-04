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
typedef  unsigned int u16 ;
struct iio_dev {int dummy; } ;
struct iio_chan_spec {int type; scalar_t__ channel; } ;
struct ad7291_chip_info {unsigned int command; unsigned int c_mask; int /*<<< orphan*/  state_lock; } ;
typedef  enum iio_event_type { ____Placeholder_iio_event_type } iio_event_type ;
typedef  enum iio_event_direction { ____Placeholder_iio_event_direction } iio_event_direction ;

/* Variables and functions */
 unsigned int AD7291_AUTOCYCLE ; 
 int /*<<< orphan*/  AD7291_COMMAND ; 
 unsigned int BIT (scalar_t__) ; 
 int EINVAL ; 
#define  IIO_VOLTAGE 128 
 int ad7291_i2c_write (struct ad7291_chip_info*,int /*<<< orphan*/ ,unsigned int) ; 
 struct ad7291_chip_info* iio_priv (struct iio_dev*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ad7291_write_event_config(struct iio_dev *indio_dev,
				     const struct iio_chan_spec *chan,
				     enum iio_event_type type,
				     enum iio_event_direction dir,
				     int state)
{
	int ret = 0;
	struct ad7291_chip_info *chip = iio_priv(indio_dev);
	unsigned int mask;
	u16 regval;

	mutex_lock(&chip->state_lock);
	regval = chip->command;
	/*
	 * To be enabled the channel must simply be on. If any are enabled
	 * use continuous sampling mode.
	 * Possible to disable temp as well but that makes single read tricky.
	 */

	mask = BIT(15 - chan->channel);

	switch (chan->type) {
	case IIO_VOLTAGE:
		if ((!state) && (chip->c_mask & mask))
			chip->c_mask &= ~mask;
		else if (state && (!(chip->c_mask & mask)))
			chip->c_mask |= mask;
		else
			break;

		regval &= ~AD7291_AUTOCYCLE;
		regval |= chip->c_mask;
		if (chip->c_mask) /* Enable autocycle? */
			regval |= AD7291_AUTOCYCLE;

		ret = ad7291_i2c_write(chip, AD7291_COMMAND, regval);
		if (ret < 0)
			goto error_ret;

		chip->command = regval;
		break;
	default:
		ret = -EINVAL;
	}

error_ret:
	mutex_unlock(&chip->state_lock);
	return ret;
}