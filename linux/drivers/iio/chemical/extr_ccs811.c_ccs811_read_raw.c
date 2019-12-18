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
struct iio_chan_spec {int /*<<< orphan*/  channel2; int /*<<< orphan*/  type; } ;
struct TYPE_2__ {int /*<<< orphan*/  voc; int /*<<< orphan*/  co2; int /*<<< orphan*/  raw_data; } ;
struct ccs811_data {int /*<<< orphan*/  lock; TYPE_1__ buffer; } ;

/* Variables and functions */
 int CCS811_VOLTAGE_MASK ; 
 int EINVAL ; 
#define  IIO_CHAN_INFO_RAW 134 
#define  IIO_CHAN_INFO_SCALE 133 
#define  IIO_CONCENTRATION 132 
#define  IIO_CURRENT 131 
#define  IIO_MOD_CO2 130 
#define  IIO_MOD_VOC 129 
 int IIO_VAL_INT ; 
 int IIO_VAL_INT_PLUS_MICRO ; 
 int IIO_VAL_INT_PLUS_NANO ; 
#define  IIO_VOLTAGE 128 
 int be16_to_cpu (int /*<<< orphan*/ ) ; 
 int ccs811_get_measurement (struct ccs811_data*) ; 
 int iio_device_claim_direct_mode (struct iio_dev*) ; 
 int /*<<< orphan*/  iio_device_release_direct_mode (struct iio_dev*) ; 
 struct ccs811_data* iio_priv (struct iio_dev*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ccs811_read_raw(struct iio_dev *indio_dev,
			   struct iio_chan_spec const *chan,
			   int *val, int *val2, long mask)
{
	struct ccs811_data *data = iio_priv(indio_dev);
	int ret;

	switch (mask) {
	case IIO_CHAN_INFO_RAW:
		ret = iio_device_claim_direct_mode(indio_dev);
		if (ret)
			return ret;
		mutex_lock(&data->lock);
		ret = ccs811_get_measurement(data);
		if (ret < 0) {
			mutex_unlock(&data->lock);
			iio_device_release_direct_mode(indio_dev);
			return ret;
		}

		switch (chan->type) {
		case IIO_VOLTAGE:
			*val = be16_to_cpu(data->buffer.raw_data) &
					   CCS811_VOLTAGE_MASK;
			ret = IIO_VAL_INT;
			break;
		case IIO_CURRENT:
			*val = be16_to_cpu(data->buffer.raw_data) >> 10;
			ret = IIO_VAL_INT;
			break;
		case IIO_CONCENTRATION:
			switch (chan->channel2) {
			case IIO_MOD_CO2:
				*val = be16_to_cpu(data->buffer.co2);
				ret =  IIO_VAL_INT;
				break;
			case IIO_MOD_VOC:
				*val = be16_to_cpu(data->buffer.voc);
				ret = IIO_VAL_INT;
				break;
			default:
				ret = -EINVAL;
			}
			break;
		default:
			ret = -EINVAL;
		}
		mutex_unlock(&data->lock);
		iio_device_release_direct_mode(indio_dev);

		return ret;

	case IIO_CHAN_INFO_SCALE:
		switch (chan->type) {
		case IIO_VOLTAGE:
			*val = 1;
			*val2 = 612903;
			return IIO_VAL_INT_PLUS_MICRO;
		case IIO_CURRENT:
			*val = 0;
			*val2 = 1000;
			return IIO_VAL_INT_PLUS_MICRO;
		case IIO_CONCENTRATION:
			switch (chan->channel2) {
			case IIO_MOD_CO2:
				*val = 0;
				*val2 = 100;
				return IIO_VAL_INT_PLUS_MICRO;
			case IIO_MOD_VOC:
				*val = 0;
				*val2 = 100;
				return IIO_VAL_INT_PLUS_NANO;
			default:
				return -EINVAL;
			}
		default:
			return -EINVAL;
		}
	default:
		return -EINVAL;
	}
}