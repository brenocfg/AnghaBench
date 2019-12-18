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
struct iio_dev {int dummy; } ;
struct iio_chan_spec {int /*<<< orphan*/  address; } ;
struct cm3323_data {int /*<<< orphan*/  mutex; int /*<<< orphan*/  client; } ;
struct TYPE_2__ {int val; int val2; } ;

/* Variables and functions */
 int EINVAL ; 
#define  IIO_CHAN_INFO_INT_TIME 129 
#define  IIO_CHAN_INFO_RAW 128 
 int IIO_VAL_INT ; 
 int IIO_VAL_INT_PLUS_MICRO ; 
 int cm3323_get_it_bits (struct cm3323_data*) ; 
 TYPE_1__* cm3323_int_time ; 
 int i2c_smbus_read_word_data (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct cm3323_data* iio_priv (struct iio_dev*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int cm3323_read_raw(struct iio_dev *indio_dev,
			   struct iio_chan_spec const *chan, int *val,
			   int *val2, long mask)
{
	int ret;
	struct cm3323_data *data = iio_priv(indio_dev);

	switch (mask) {
	case IIO_CHAN_INFO_RAW:
		mutex_lock(&data->mutex);
		ret = i2c_smbus_read_word_data(data->client, chan->address);
		if (ret < 0) {
			mutex_unlock(&data->mutex);
			return ret;
		}
		*val = ret;
		mutex_unlock(&data->mutex);

		return IIO_VAL_INT;
	case IIO_CHAN_INFO_INT_TIME:
		mutex_lock(&data->mutex);
		ret = cm3323_get_it_bits(data);
		if (ret < 0) {
			mutex_unlock(&data->mutex);
			return ret;
		}

		*val = cm3323_int_time[ret].val;
		*val2 = cm3323_int_time[ret].val2;
		mutex_unlock(&data->mutex);

		return IIO_VAL_INT_PLUS_MICRO;
	default:
		return -EINVAL;
	}
}