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
struct max44000_data {int /*<<< orphan*/  lock; int /*<<< orphan*/  regmap; } ;
struct iio_dev {int dummy; } ;
struct iio_chan_spec {int /*<<< orphan*/  type; } ;

/* Variables and functions */
 int EINVAL ; 
#define  IIO_CHAN_INFO_INT_TIME 133 
#define  IIO_CHAN_INFO_RAW 132 
#define  IIO_CHAN_INFO_SCALE 131 
#define  IIO_CURRENT 130 
#define  IIO_LIGHT 129 
#define  IIO_PROXIMITY 128 
 int IIO_VAL_FRACTIONAL_LOG2 ; 
 int IIO_VAL_INT ; 
 int IIO_VAL_INT_PLUS_NANO ; 
 int MAX44000_ALSPGA_MAX_SHIFT ; 
 int MAX44000_ALS_TO_LUX_DEFAULT_FRACTION_LOG2 ; 
 int /*<<< orphan*/  MAX44000_REG_PRX_DATA ; 
 struct max44000_data* iio_priv (struct iio_dev*) ; 
 int* max44000_alspga_shift ; 
 int* max44000_int_time_avail_ns_array ; 
 int max44000_read_alspga (struct max44000_data*) ; 
 int max44000_read_alstim (struct max44000_data*) ; 
 int max44000_read_alsval (struct max44000_data*) ; 
 int max44000_read_led_current_raw (struct max44000_data*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int*) ; 

__attribute__((used)) static int max44000_read_raw(struct iio_dev *indio_dev,
			     struct iio_chan_spec const *chan,
			     int *val, int *val2, long mask)
{
	struct max44000_data *data = iio_priv(indio_dev);
	int alstim, alspga;
	unsigned int regval;
	int ret;

	switch (mask) {
	case IIO_CHAN_INFO_RAW:
		switch (chan->type) {
		case IIO_LIGHT:
			mutex_lock(&data->lock);
			ret = max44000_read_alsval(data);
			mutex_unlock(&data->lock);
			if (ret < 0)
				return ret;
			*val = ret;
			return IIO_VAL_INT;

		case IIO_PROXIMITY:
			mutex_lock(&data->lock);
			ret = regmap_read(data->regmap, MAX44000_REG_PRX_DATA, &regval);
			mutex_unlock(&data->lock);
			if (ret < 0)
				return ret;
			*val = regval;
			return IIO_VAL_INT;

		case IIO_CURRENT:
			mutex_lock(&data->lock);
			ret = max44000_read_led_current_raw(data);
			mutex_unlock(&data->lock);
			if (ret < 0)
				return ret;
			*val = ret;
			return IIO_VAL_INT;

		default:
			return -EINVAL;
		}

	case IIO_CHAN_INFO_SCALE:
		switch (chan->type) {
		case IIO_CURRENT:
			/* Output register is in 10s of miliamps */
			*val = 10;
			return IIO_VAL_INT;

		case IIO_LIGHT:
			mutex_lock(&data->lock);
			alspga = ret = max44000_read_alspga(data);
			mutex_unlock(&data->lock);
			if (ret < 0)
				return ret;

			/* Avoid negative shifts */
			*val = (1 << MAX44000_ALSPGA_MAX_SHIFT);
			*val2 = MAX44000_ALS_TO_LUX_DEFAULT_FRACTION_LOG2
					+ MAX44000_ALSPGA_MAX_SHIFT
					- max44000_alspga_shift[alspga];
			return IIO_VAL_FRACTIONAL_LOG2;

		default:
			return -EINVAL;
		}

	case IIO_CHAN_INFO_INT_TIME:
		mutex_lock(&data->lock);
		alstim = ret = max44000_read_alstim(data);
		mutex_unlock(&data->lock);

		if (ret < 0)
			return ret;
		*val = 0;
		*val2 = max44000_int_time_avail_ns_array[alstim];
		return IIO_VAL_INT_PLUS_NANO;

	default:
		return -EINVAL;
	}
}