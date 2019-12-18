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
struct iio_chan_spec {int /*<<< orphan*/  type; int /*<<< orphan*/  address; } ;
struct apds9960_data {int als_adc_int_us; size_t pxs_gain; size_t als_gain; int /*<<< orphan*/  lock; int /*<<< orphan*/  regmap; scalar_t__ gesture_mode_running; } ;
typedef  int /*<<< orphan*/  __le16 ;

/* Variables and functions */
 int EBUSY ; 
 int EINVAL ; 
#define  IIO_CHAN_INFO_INT_TIME 132 
#define  IIO_CHAN_INFO_RAW 131 
#define  IIO_CHAN_INFO_SCALE 130 
#define  IIO_INTENSITY 129 
#define  IIO_PROXIMITY 128 
 int IIO_VAL_INT ; 
 int IIO_VAL_INT_PLUS_MICRO ; 
 int* apds9960_als_gain_map ; 
 int* apds9960_pxs_gain_map ; 
 int /*<<< orphan*/  apds9960_set_power_state (struct apds9960_data*,int) ; 
 struct apds9960_data* iio_priv (struct iio_dev*) ; 
 int le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int regmap_bulk_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static int apds9960_read_raw(struct iio_dev *indio_dev,
			     struct iio_chan_spec const *chan,
			     int *val, int *val2, long mask)
{
	struct apds9960_data *data = iio_priv(indio_dev);
	__le16 buf;
	int ret = -EINVAL;

	if (data->gesture_mode_running)
		return -EBUSY;

	switch (mask) {
	case IIO_CHAN_INFO_RAW:
		apds9960_set_power_state(data, true);
		switch (chan->type) {
		case IIO_PROXIMITY:
			ret = regmap_read(data->regmap, chan->address, val);
			if (!ret)
				ret = IIO_VAL_INT;
			break;
		case IIO_INTENSITY:
			ret = regmap_bulk_read(data->regmap, chan->address,
					       &buf, 2);
			if (!ret) {
				ret = IIO_VAL_INT;
				*val = le16_to_cpu(buf);
			}
			break;
		default:
			ret = -EINVAL;
		}
		apds9960_set_power_state(data, false);
		break;
	case IIO_CHAN_INFO_INT_TIME:
		/* RGB + ALS sensors only have integration time */
		mutex_lock(&data->lock);
		switch (chan->type) {
		case IIO_INTENSITY:
			*val = 0;
			*val2 = data->als_adc_int_us;
			ret = IIO_VAL_INT_PLUS_MICRO;
			break;
		default:
			ret = -EINVAL;
		}
		mutex_unlock(&data->lock);
		break;
	case IIO_CHAN_INFO_SCALE:
		mutex_lock(&data->lock);
		switch (chan->type) {
		case IIO_PROXIMITY:
			*val = apds9960_pxs_gain_map[data->pxs_gain];
			ret = IIO_VAL_INT;
			break;
		case IIO_INTENSITY:
			*val = apds9960_als_gain_map[data->als_gain];
			ret = IIO_VAL_INT;
			break;
		default:
			ret = -EINVAL;
		}
		mutex_unlock(&data->lock);
		break;
	}

	return ret;
}