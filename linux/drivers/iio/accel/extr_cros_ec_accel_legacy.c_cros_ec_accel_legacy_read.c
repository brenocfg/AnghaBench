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
struct cros_ec_sensors_core_state {int (* read_ec_sensors_data ) (struct iio_dev*,int,int*) ;int /*<<< orphan*/  cmd_lock; int /*<<< orphan*/  type; } ;
typedef  int s16 ;

/* Variables and functions */
 int ACCEL_LEGACY_NSCALE ; 
#define  IIO_CHAN_INFO_CALIBBIAS 130 
#define  IIO_CHAN_INFO_RAW 129 
#define  IIO_CHAN_INFO_SCALE 128 
 int IIO_VAL_INT ; 
 int IIO_VAL_INT_PLUS_NANO ; 
 int /*<<< orphan*/  MOTIONSENSE_TYPE_ACCEL ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int cros_ec_sensors_core_read (struct cros_ec_sensors_core_state*,struct iio_chan_spec const*,int*,int*,long) ; 
 struct cros_ec_sensors_core_state* iio_priv (struct iio_dev*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int stub1 (struct iio_dev*,int,int*) ; 

__attribute__((used)) static int cros_ec_accel_legacy_read(struct iio_dev *indio_dev,
				     struct iio_chan_spec const *chan,
				     int *val, int *val2, long mask)
{
	struct cros_ec_sensors_core_state *st = iio_priv(indio_dev);
	s16 data = 0;
	int ret;
	int idx = chan->scan_index;

	mutex_lock(&st->cmd_lock);

	switch (mask) {
	case IIO_CHAN_INFO_RAW:
		ret = st->read_ec_sensors_data(indio_dev, 1 << idx, &data);
		if (ret < 0)
			break;
		ret = IIO_VAL_INT;
		*val = data;
		break;
	case IIO_CHAN_INFO_SCALE:
		WARN_ON(st->type != MOTIONSENSE_TYPE_ACCEL);
		*val = 0;
		*val2 = ACCEL_LEGACY_NSCALE;
		ret = IIO_VAL_INT_PLUS_NANO;
		break;
	case IIO_CHAN_INFO_CALIBBIAS:
		/* Calibration not supported. */
		*val = 0;
		ret = IIO_VAL_INT;
		break;
	default:
		ret = cros_ec_sensors_core_read(st, chan, val, val2,
				mask);
		break;
	}
	mutex_unlock(&st->cmd_lock);

	return ret;
}