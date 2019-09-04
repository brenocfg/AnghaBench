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
struct ms_ht_dev {size_t res_index; } ;
struct iio_dev {int dummy; } ;
struct iio_chan_spec {int /*<<< orphan*/  type; } ;
typedef  int s32 ;

/* Variables and functions */
 int EINVAL ; 
#define  IIO_CHAN_INFO_PROCESSED 130 
#define  IIO_CHAN_INFO_SAMP_FREQ 129 
#define  IIO_TEMP 128 
 int IIO_VAL_INT ; 
 struct ms_ht_dev* iio_priv (struct iio_dev*) ; 
 int ms_sensors_ht_read_temperature (struct ms_ht_dev*,int*) ; 
 int* tsys02d_samp_freq ; 

__attribute__((used)) static int tsys02d_read_raw(struct iio_dev *indio_dev,
			    struct iio_chan_spec const *channel, int *val,
			    int *val2, long mask)
{
	int ret;
	s32 temperature;
	struct ms_ht_dev *dev_data = iio_priv(indio_dev);

	switch (mask) {
	case IIO_CHAN_INFO_PROCESSED:
		switch (channel->type) {
		case IIO_TEMP:	/* in milli °C */
			ret = ms_sensors_ht_read_temperature(dev_data,
							     &temperature);
			if (ret)
				return ret;
			*val = temperature;

			return IIO_VAL_INT;
		default:
			return -EINVAL;
		}
	case IIO_CHAN_INFO_SAMP_FREQ:
		*val = tsys02d_samp_freq[dev_data->res_index];

		return IIO_VAL_INT;
	default:
		return -EINVAL;
	}
}