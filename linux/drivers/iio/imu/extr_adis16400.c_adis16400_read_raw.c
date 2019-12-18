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
struct iio_dev {int /*<<< orphan*/  mlock; } ;
struct iio_chan_spec {size_t scan_index; int /*<<< orphan*/  channel; int /*<<< orphan*/  type; } ;
struct adis16400_state {TYPE_1__* variant; int /*<<< orphan*/  adis; } ;
typedef  int int16_t ;
struct TYPE_2__ {int gyro_scale_micro; int accel_scale_micro; int temp_scale_nano; int temp_offset; int (* get_freq ) (struct adis16400_state*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  ADIS16400_SENS_AVG ; 
 int EINVAL ; 
#define  IIO_ACCEL 139 
#define  IIO_ANGL_VEL 138 
#define  IIO_CHAN_INFO_CALIBBIAS 137 
#define  IIO_CHAN_INFO_LOW_PASS_FILTER_3DB_FREQUENCY 136 
#define  IIO_CHAN_INFO_OFFSET 135 
#define  IIO_CHAN_INFO_RAW 134 
#define  IIO_CHAN_INFO_SAMP_FREQ 133 
#define  IIO_CHAN_INFO_SCALE 132 
#define  IIO_MAGN 131 
#define  IIO_PRESSURE 130 
#define  IIO_TEMP 129 
 int IIO_VAL_INT ; 
 int IIO_VAL_INT_PLUS_MICRO ; 
#define  IIO_VOLTAGE 128 
 int* adis16400_3db_divisors ; 
 int /*<<< orphan*/ * adis16400_addresses ; 
 int adis_read_reg_16 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int*) ; 
 int adis_single_conversion (struct iio_dev*,struct iio_chan_spec const*,int /*<<< orphan*/ ,int*) ; 
 struct adis16400_state* iio_priv (struct iio_dev*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int sign_extend32 (int,int) ; 
 int stub1 (struct adis16400_state*) ; 
 int stub2 (struct adis16400_state*) ; 

__attribute__((used)) static int adis16400_read_raw(struct iio_dev *indio_dev,
	struct iio_chan_spec const *chan, int *val, int *val2, long info)
{
	struct adis16400_state *st = iio_priv(indio_dev);
	int16_t val16;
	int ret;

	switch (info) {
	case IIO_CHAN_INFO_RAW:
		return adis_single_conversion(indio_dev, chan, 0, val);
	case IIO_CHAN_INFO_SCALE:
		switch (chan->type) {
		case IIO_ANGL_VEL:
			*val = 0;
			*val2 = st->variant->gyro_scale_micro;
			return IIO_VAL_INT_PLUS_MICRO;
		case IIO_VOLTAGE:
			*val = 0;
			if (chan->channel == 0) {
				*val = 2;
				*val2 = 418000; /* 2.418 mV */
			} else {
				*val = 0;
				*val2 = 805800; /* 805.8 uV */
			}
			return IIO_VAL_INT_PLUS_MICRO;
		case IIO_ACCEL:
			*val = 0;
			*val2 = st->variant->accel_scale_micro;
			return IIO_VAL_INT_PLUS_MICRO;
		case IIO_MAGN:
			*val = 0;
			*val2 = 500; /* 0.5 mgauss */
			return IIO_VAL_INT_PLUS_MICRO;
		case IIO_TEMP:
			*val = st->variant->temp_scale_nano / 1000000;
			*val2 = (st->variant->temp_scale_nano % 1000000);
			return IIO_VAL_INT_PLUS_MICRO;
		case IIO_PRESSURE:
			/* 20 uBar = 0.002kPascal */
			*val = 0;
			*val2 = 2000;
			return IIO_VAL_INT_PLUS_MICRO;
		default:
			return -EINVAL;
		}
	case IIO_CHAN_INFO_CALIBBIAS:
		mutex_lock(&indio_dev->mlock);
		ret = adis_read_reg_16(&st->adis,
				adis16400_addresses[chan->scan_index], &val16);
		mutex_unlock(&indio_dev->mlock);
		if (ret)
			return ret;
		val16 = sign_extend32(val16, 11);
		*val = val16;
		return IIO_VAL_INT;
	case IIO_CHAN_INFO_OFFSET:
		/* currently only temperature */
		*val = st->variant->temp_offset;
		return IIO_VAL_INT;
	case IIO_CHAN_INFO_LOW_PASS_FILTER_3DB_FREQUENCY:
		mutex_lock(&indio_dev->mlock);
		/* Need both the number of taps and the sampling frequency */
		ret = adis_read_reg_16(&st->adis,
						ADIS16400_SENS_AVG,
						&val16);
		if (ret < 0) {
			mutex_unlock(&indio_dev->mlock);
			return ret;
		}
		ret = st->variant->get_freq(st);
		if (ret >= 0) {
			ret /= adis16400_3db_divisors[val16 & 0x07];
			*val = ret / 1000;
			*val2 = (ret % 1000) * 1000;
		}
		mutex_unlock(&indio_dev->mlock);
		if (ret < 0)
			return ret;
		return IIO_VAL_INT_PLUS_MICRO;
	case IIO_CHAN_INFO_SAMP_FREQ:
		ret = st->variant->get_freq(st);
		if (ret < 0)
			return ret;
		*val = ret / 1000;
		*val2 = (ret % 1000) * 1000;
		return IIO_VAL_INT_PLUS_MICRO;
	default:
		return -EINVAL;
	}
}