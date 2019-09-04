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
struct iio_chan_spec {int scan_index; } ;
struct cros_ec_accel_legacy_state {int dummy; } ;
typedef  int s16 ;

/* Variables and functions */
 int ACCEL_LEGACY_NSCALE ; 
 int EINVAL ; 
#define  IIO_CHAN_INFO_CALIBBIAS 130 
#define  IIO_CHAN_INFO_RAW 129 
#define  IIO_CHAN_INFO_SCALE 128 
 int IIO_VAL_INT ; 
 int IIO_VAL_INT_PLUS_NANO ; 
 struct cros_ec_accel_legacy_state* iio_priv (struct iio_dev*) ; 
 int read_ec_accel_data (struct cros_ec_accel_legacy_state*,int,int*) ; 

__attribute__((used)) static int cros_ec_accel_legacy_read(struct iio_dev *indio_dev,
				     struct iio_chan_spec const *chan,
				     int *val, int *val2, long mask)
{
	struct cros_ec_accel_legacy_state *st = iio_priv(indio_dev);
	s16 data = 0;
	int ret = IIO_VAL_INT;

	switch (mask) {
	case IIO_CHAN_INFO_RAW:
		ret = read_ec_accel_data(st, (1 << chan->scan_index), &data);
		if (ret)
			return ret;
		*val = data;
		return IIO_VAL_INT;
	case IIO_CHAN_INFO_SCALE:
		*val = 0;
		*val2 = ACCEL_LEGACY_NSCALE;
		return IIO_VAL_INT_PLUS_NANO;
	case IIO_CHAN_INFO_CALIBBIAS:
		/* Calibration not supported. */
		*val = 0;
		return IIO_VAL_INT;
	default:
		return -EINVAL;
	}
}