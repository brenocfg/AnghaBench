#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int u16 ;
struct iio_dev {int dummy; } ;
struct iio_chan_spec {int scan_index; } ;
struct TYPE_7__ {int /*<<< orphan*/  data; } ;
struct TYPE_8__ {TYPE_1__ sensor_range; int /*<<< orphan*/  cmd; } ;
struct TYPE_11__ {int /*<<< orphan*/  cmd_lock; TYPE_4__* resp; TYPE_2__ param; } ;
struct cros_ec_baro_state {TYPE_5__ core; } ;
typedef  int /*<<< orphan*/  s16 ;
struct TYPE_9__ {int ret; } ;
struct TYPE_10__ {TYPE_3__ sensor_range; } ;

/* Variables and functions */
 int CROS_EC_SENSOR_BITS ; 
 int /*<<< orphan*/  EC_MOTION_SENSE_NO_VALUE ; 
#define  IIO_CHAN_INFO_RAW 129 
#define  IIO_CHAN_INFO_SCALE 128 
 int IIO_VAL_FRACTIONAL ; 
 int IIO_VAL_INT ; 
 int /*<<< orphan*/  MOTIONSENSE_CMD_SENSOR_RANGE ; 
 int cros_ec_motion_send_host_cmd (TYPE_5__*,int /*<<< orphan*/ ) ; 
 int cros_ec_sensors_core_read (TYPE_5__*,struct iio_chan_spec const*,int*,int*,long) ; 
 int cros_ec_sensors_read_cmd (struct iio_dev*,int,int /*<<< orphan*/ *) ; 
 struct cros_ec_baro_state* iio_priv (struct iio_dev*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int cros_ec_baro_read(struct iio_dev *indio_dev,
			     struct iio_chan_spec const *chan,
			     int *val, int *val2, long mask)
{
	struct cros_ec_baro_state *st = iio_priv(indio_dev);
	u16 data = 0;
	int ret;
	int idx = chan->scan_index;

	mutex_lock(&st->core.cmd_lock);

	switch (mask) {
	case IIO_CHAN_INFO_RAW:
		ret = cros_ec_sensors_read_cmd(indio_dev, 1 << idx,
					     (s16 *)&data);
		if (ret)
			break;

		*val = data;
		ret = IIO_VAL_INT;
		break;
	case IIO_CHAN_INFO_SCALE:
		st->core.param.cmd = MOTIONSENSE_CMD_SENSOR_RANGE;
		st->core.param.sensor_range.data = EC_MOTION_SENSE_NO_VALUE;

		ret = cros_ec_motion_send_host_cmd(&st->core, 0);
		if (ret)
			break;

		*val = st->core.resp->sensor_range.ret;

		/* scale * in_pressure_raw --> kPa */
		*val2 = 10 << CROS_EC_SENSOR_BITS;
		ret = IIO_VAL_FRACTIONAL;
		break;
	default:
		ret = cros_ec_sensors_core_read(&st->core, chan, val, val2,
						mask);
		break;
	}

	mutex_unlock(&st->core.cmd_lock);

	return ret;
}