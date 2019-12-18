#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct iio_chan_spec {int dummy; } ;
struct TYPE_9__ {void* data; } ;
struct TYPE_7__ {void* data; } ;
struct TYPE_10__ {TYPE_3__ sensor_odr; int /*<<< orphan*/  cmd; TYPE_1__ ec_rate; } ;
struct cros_ec_sensors_core_state {TYPE_6__* resp; TYPE_4__ param; } ;
struct TYPE_11__ {int ret; } ;
struct TYPE_8__ {int ret; } ;
struct TYPE_12__ {TYPE_5__ sensor_odr; TYPE_2__ ec_rate; } ;

/* Variables and functions */
 void* EC_MOTION_SENSE_NO_VALUE ; 
 int EINVAL ; 
#define  IIO_CHAN_INFO_FREQUENCY 129 
#define  IIO_CHAN_INFO_SAMP_FREQ 128 
 int IIO_VAL_INT ; 
 int /*<<< orphan*/  MOTIONSENSE_CMD_EC_RATE ; 
 int /*<<< orphan*/  MOTIONSENSE_CMD_SENSOR_ODR ; 
 int cros_ec_motion_send_host_cmd (struct cros_ec_sensors_core_state*,int /*<<< orphan*/ ) ; 

int cros_ec_sensors_core_read(struct cros_ec_sensors_core_state *st,
			  struct iio_chan_spec const *chan,
			  int *val, int *val2, long mask)
{
	int ret;

	switch (mask) {
	case IIO_CHAN_INFO_SAMP_FREQ:
		st->param.cmd = MOTIONSENSE_CMD_EC_RATE;
		st->param.ec_rate.data =
			EC_MOTION_SENSE_NO_VALUE;

		ret = cros_ec_motion_send_host_cmd(st, 0);
		if (ret)
			break;

		*val = st->resp->ec_rate.ret;
		ret = IIO_VAL_INT;
		break;
	case IIO_CHAN_INFO_FREQUENCY:
		st->param.cmd = MOTIONSENSE_CMD_SENSOR_ODR;
		st->param.sensor_odr.data =
			EC_MOTION_SENSE_NO_VALUE;

		ret = cros_ec_motion_send_host_cmd(st, 0);
		if (ret)
			break;

		*val = st->resp->sensor_odr.ret;
		ret = IIO_VAL_INT;
		break;
	default:
		ret = -EINVAL;
		break;
	}

	return ret;
}