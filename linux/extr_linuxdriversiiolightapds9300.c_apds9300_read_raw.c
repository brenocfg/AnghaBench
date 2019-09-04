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
struct iio_chan_spec {int type; int channel; } ;
struct apds9300_data {int /*<<< orphan*/  mutex; } ;

/* Variables and functions */
 int EINVAL ; 
#define  IIO_INTENSITY 129 
#define  IIO_LIGHT 128 
 int IIO_VAL_INT ; 
 int apds9300_calculate_lux (int,int) ; 
 int apds9300_get_adc_val (struct apds9300_data*,int) ; 
 struct apds9300_data* iio_priv (struct iio_dev*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int apds9300_read_raw(struct iio_dev *indio_dev,
		struct iio_chan_spec const *chan, int *val, int *val2,
		long mask)
{
	int ch0, ch1, ret = -EINVAL;
	struct apds9300_data *data = iio_priv(indio_dev);

	mutex_lock(&data->mutex);
	switch (chan->type) {
	case IIO_LIGHT:
		ch0 = apds9300_get_adc_val(data, 0);
		if (ch0 < 0) {
			ret = ch0;
			break;
		}
		ch1 = apds9300_get_adc_val(data, 1);
		if (ch1 < 0) {
			ret = ch1;
			break;
		}
		*val = apds9300_calculate_lux(ch0, ch1);
		ret = IIO_VAL_INT;
		break;
	case IIO_INTENSITY:
		ret = apds9300_get_adc_val(data, chan->channel);
		if (ret < 0)
			break;
		*val = ret;
		ret = IIO_VAL_INT;
		break;
	default:
		break;
	}
	mutex_unlock(&data->mutex);

	return ret;
}