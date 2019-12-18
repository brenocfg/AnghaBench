#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_8__ ;
typedef  struct TYPE_16__   TYPE_7__ ;
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int u16 ;
struct iio_dev {int dummy; } ;
struct iio_chan_spec {int scan_index; int /*<<< orphan*/  type; } ;
struct TYPE_13__ {int /*<<< orphan*/  data; } ;
struct TYPE_10__ {int /*<<< orphan*/  flags; } ;
struct TYPE_14__ {TYPE_4__ sensor_range; int /*<<< orphan*/  cmd; TYPE_1__ sensor_offset; } ;
struct TYPE_17__ {int /*<<< orphan*/  cmd_lock; TYPE_7__* resp; TYPE_5__ param; TYPE_3__* calib; } ;
struct cros_ec_light_prox_state {TYPE_8__ core; } ;
typedef  int s64 ;
typedef  int /*<<< orphan*/  s16 ;
struct TYPE_15__ {int ret; } ;
struct TYPE_11__ {int* offset; } ;
struct TYPE_16__ {TYPE_6__ sensor_range; TYPE_2__ sensor_offset; } ;
struct TYPE_12__ {int offset; } ;

/* Variables and functions */
 int /*<<< orphan*/  EC_MOTION_SENSE_NO_VALUE ; 
 int EINVAL ; 
#define  IIO_CHAN_INFO_CALIBBIAS 131 
#define  IIO_CHAN_INFO_CALIBSCALE 130 
#define  IIO_CHAN_INFO_PROCESSED 129 
#define  IIO_CHAN_INFO_RAW 128 
 int /*<<< orphan*/  IIO_LIGHT ; 
 int /*<<< orphan*/  IIO_PROXIMITY ; 
 int IIO_VAL_INT ; 
 int IIO_VAL_INT_PLUS_MICRO ; 
 int /*<<< orphan*/  MOTIONSENSE_CMD_SENSOR_OFFSET ; 
 int /*<<< orphan*/  MOTIONSENSE_CMD_SENSOR_RANGE ; 
 int cros_ec_motion_send_host_cmd (TYPE_8__*,int /*<<< orphan*/ ) ; 
 int cros_ec_sensors_core_read (TYPE_8__*,struct iio_chan_spec const*,int*,int*,long) ; 
 int cros_ec_sensors_read_cmd (struct iio_dev*,int,int /*<<< orphan*/ *) ; 
 struct cros_ec_light_prox_state* iio_priv (struct iio_dev*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int cros_ec_light_prox_read(struct iio_dev *indio_dev,
				   struct iio_chan_spec const *chan,
				   int *val, int *val2, long mask)
{
	struct cros_ec_light_prox_state *st = iio_priv(indio_dev);
	u16 data = 0;
	s64 val64;
	int ret;
	int idx = chan->scan_index;

	mutex_lock(&st->core.cmd_lock);

	switch (mask) {
	case IIO_CHAN_INFO_RAW:
		if (chan->type == IIO_PROXIMITY) {
			ret = cros_ec_sensors_read_cmd(indio_dev, 1 << idx,
						     (s16 *)&data);
			if (ret)
				break;
			*val = data;
			ret = IIO_VAL_INT;
		} else {
			ret = -EINVAL;
		}
		break;
	case IIO_CHAN_INFO_PROCESSED:
		if (chan->type == IIO_LIGHT) {
			ret = cros_ec_sensors_read_cmd(indio_dev, 1 << idx,
						     (s16 *)&data);
			if (ret)
				break;
			/*
			 * The data coming from the light sensor is
			 * pre-processed and represents the ambient light
			 * illuminance reading expressed in lux.
			 */
			*val = data;
			ret = IIO_VAL_INT;
		} else {
			ret = -EINVAL;
		}
		break;
	case IIO_CHAN_INFO_CALIBBIAS:
		st->core.param.cmd = MOTIONSENSE_CMD_SENSOR_OFFSET;
		st->core.param.sensor_offset.flags = 0;

		ret = cros_ec_motion_send_host_cmd(&st->core, 0);
		if (ret)
			break;

		/* Save values */
		st->core.calib[0].offset =
			st->core.resp->sensor_offset.offset[0];

		*val = st->core.calib[idx].offset;
		ret = IIO_VAL_INT;
		break;
	case IIO_CHAN_INFO_CALIBSCALE:
		/*
		 * RANGE is used for calibration
		 * scale is a number x.y, where x is coded on 16 bits,
		 * y coded on 16 bits, between 0 and 9999.
		 */
		st->core.param.cmd = MOTIONSENSE_CMD_SENSOR_RANGE;
		st->core.param.sensor_range.data = EC_MOTION_SENSE_NO_VALUE;

		ret = cros_ec_motion_send_host_cmd(&st->core, 0);
		if (ret)
			break;

		val64 = st->core.resp->sensor_range.ret;
		*val = val64 >> 16;
		*val2 = (val64 & 0xffff) * 100;
		ret = IIO_VAL_INT_PLUS_MICRO;
		break;
	default:
		ret = cros_ec_sensors_core_read(&st->core, chan, val, val2,
						mask);
		break;
	}

	mutex_unlock(&st->core.cmd_lock);

	return ret;
}