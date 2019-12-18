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
struct iio_dev {int dummy; } ;
struct iio_chan_spec {int scan_index; } ;
struct TYPE_9__ {int data; } ;
struct TYPE_8__ {int* offset; int /*<<< orphan*/  temp; int /*<<< orphan*/  flags; } ;
struct TYPE_10__ {TYPE_3__ sensor_range; int /*<<< orphan*/  cmd; TYPE_2__ sensor_offset; } ;
struct TYPE_11__ {int /*<<< orphan*/  cmd_lock; TYPE_4__ param; TYPE_1__* calib; } ;
struct cros_ec_light_prox_state {TYPE_5__ core; } ;
struct TYPE_7__ {int offset; } ;

/* Variables and functions */
 int /*<<< orphan*/  EC_MOTION_SENSE_INVALID_CALIB_TEMP ; 
#define  IIO_CHAN_INFO_CALIBBIAS 129 
#define  IIO_CHAN_INFO_CALIBSCALE 128 
 int /*<<< orphan*/  MOTIONSENSE_CMD_SENSOR_OFFSET ; 
 int /*<<< orphan*/  MOTIONSENSE_CMD_SENSOR_RANGE ; 
 int /*<<< orphan*/  MOTION_SENSE_SET_OFFSET ; 
 int cros_ec_motion_send_host_cmd (TYPE_5__*,int /*<<< orphan*/ ) ; 
 int cros_ec_sensors_core_write (TYPE_5__*,struct iio_chan_spec const*,int,int,long) ; 
 struct cros_ec_light_prox_state* iio_priv (struct iio_dev*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int cros_ec_light_prox_write(struct iio_dev *indio_dev,
			       struct iio_chan_spec const *chan,
			       int val, int val2, long mask)
{
	struct cros_ec_light_prox_state *st = iio_priv(indio_dev);
	int ret;
	int idx = chan->scan_index;

	mutex_lock(&st->core.cmd_lock);

	switch (mask) {
	case IIO_CHAN_INFO_CALIBBIAS:
		st->core.calib[idx].offset = val;
		/* Send to EC for each axis, even if not complete */
		st->core.param.cmd = MOTIONSENSE_CMD_SENSOR_OFFSET;
		st->core.param.sensor_offset.flags = MOTION_SENSE_SET_OFFSET;
		st->core.param.sensor_offset.offset[0] =
			st->core.calib[0].offset;
		st->core.param.sensor_offset.temp =
					EC_MOTION_SENSE_INVALID_CALIB_TEMP;
		ret = cros_ec_motion_send_host_cmd(&st->core, 0);
		break;
	case IIO_CHAN_INFO_CALIBSCALE:
		st->core.param.cmd = MOTIONSENSE_CMD_SENSOR_RANGE;
		st->core.param.sensor_range.data = (val << 16) | (val2 / 100);
		ret = cros_ec_motion_send_host_cmd(&st->core, 0);
		break;
	default:
		ret = cros_ec_sensors_core_write(&st->core, chan, val, val2,
						 mask);
		break;
	}

	mutex_unlock(&st->core.cmd_lock);

	return ret;
}