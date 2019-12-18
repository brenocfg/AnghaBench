#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct iio_chan_spec {int dummy; } ;
struct TYPE_4__ {int data; } ;
struct TYPE_6__ {int data; int roundup; } ;
struct TYPE_5__ {TYPE_1__ ec_rate; int /*<<< orphan*/  cmd; TYPE_3__ sensor_odr; } ;
struct cros_ec_sensors_core_state {int curr_sampl_freq; TYPE_2__ param; } ;

/* Variables and functions */
 int EINVAL ; 
#define  IIO_CHAN_INFO_FREQUENCY 129 
#define  IIO_CHAN_INFO_SAMP_FREQ 128 
 int /*<<< orphan*/  MOTIONSENSE_CMD_EC_RATE ; 
 int /*<<< orphan*/  MOTIONSENSE_CMD_SENSOR_ODR ; 
 int cros_ec_motion_send_host_cmd (struct cros_ec_sensors_core_state*,int /*<<< orphan*/ ) ; 

int cros_ec_sensors_core_write(struct cros_ec_sensors_core_state *st,
			       struct iio_chan_spec const *chan,
			       int val, int val2, long mask)
{
	int ret;

	switch (mask) {
	case IIO_CHAN_INFO_FREQUENCY:
		st->param.cmd = MOTIONSENSE_CMD_SENSOR_ODR;
		st->param.sensor_odr.data = val;

		/* Always roundup, so caller gets at least what it asks for. */
		st->param.sensor_odr.roundup = 1;

		ret = cros_ec_motion_send_host_cmd(st, 0);
		break;
	case IIO_CHAN_INFO_SAMP_FREQ:
		st->param.cmd = MOTIONSENSE_CMD_EC_RATE;
		st->param.ec_rate.data = val;

		ret = cros_ec_motion_send_host_cmd(st, 0);
		if (ret)
			break;
		st->curr_sampl_freq = val;
		break;
	default:
		ret = -EINVAL;
		break;
	}
	return ret;
}