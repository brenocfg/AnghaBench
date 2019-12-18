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
struct ms_tp_dev {size_t res_index; } ;
struct iio_dev {int dummy; } ;
struct iio_chan_spec {int /*<<< orphan*/  type; } ;

/* Variables and functions */
 int EINVAL ; 
#define  IIO_CHAN_INFO_PROCESSED 131 
#define  IIO_CHAN_INFO_SAMP_FREQ 130 
#define  IIO_PRESSURE 129 
#define  IIO_TEMP 128 
 int IIO_VAL_INT ; 
 int IIO_VAL_INT_PLUS_MICRO ; 
 struct ms_tp_dev* iio_priv (struct iio_dev*) ; 
 int* ms5637_samp_freq ; 
 int ms_sensors_read_temp_and_pressure (struct ms_tp_dev*,int*,unsigned int*) ; 

__attribute__((used)) static int ms5637_read_raw(struct iio_dev *indio_dev,
			   struct iio_chan_spec const *channel, int *val,
			   int *val2, long mask)
{
	int ret;
	int temperature;
	unsigned int pressure;
	struct ms_tp_dev *dev_data = iio_priv(indio_dev);

	switch (mask) {
	case IIO_CHAN_INFO_PROCESSED:
		ret = ms_sensors_read_temp_and_pressure(dev_data,
							&temperature,
							&pressure);
		if (ret)
			return ret;

		switch (channel->type) {
		case IIO_TEMP:	/* in milli °C */
			*val = temperature;

			return IIO_VAL_INT;
		case IIO_PRESSURE:	/* in kPa */
			*val = pressure / 1000;
			*val2 = (pressure % 1000) * 1000;

			return IIO_VAL_INT_PLUS_MICRO;
		default:
			return -EINVAL;
		}
	case IIO_CHAN_INFO_SAMP_FREQ:
		*val = ms5637_samp_freq[dev_data->res_index];

		return IIO_VAL_INT;
	default:
		return -EINVAL;
	}
}