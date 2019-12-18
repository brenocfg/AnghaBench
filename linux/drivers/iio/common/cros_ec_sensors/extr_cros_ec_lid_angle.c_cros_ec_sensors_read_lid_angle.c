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
struct iio_dev {int /*<<< orphan*/  dev; } ;
struct TYPE_4__ {int /*<<< orphan*/  cmd; } ;
struct cros_ec_sensors_core_state {TYPE_3__* resp; TYPE_1__ param; } ;
typedef  int /*<<< orphan*/  s16 ;
struct TYPE_5__ {int /*<<< orphan*/  value; } ;
struct TYPE_6__ {TYPE_2__ lid_angle; } ;

/* Variables and functions */
 int /*<<< orphan*/  MOTIONSENSE_CMD_LID_ANGLE ; 
 int cros_ec_motion_send_host_cmd (struct cros_ec_sensors_core_state*,int) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*) ; 
 struct cros_ec_sensors_core_state* iio_priv (struct iio_dev*) ; 

__attribute__((used)) static int cros_ec_sensors_read_lid_angle(struct iio_dev *indio_dev,
					  unsigned long scan_mask, s16 *data)
{
	struct cros_ec_sensors_core_state *st = iio_priv(indio_dev);
	int ret;

	st->param.cmd = MOTIONSENSE_CMD_LID_ANGLE;
	ret = cros_ec_motion_send_host_cmd(st, sizeof(st->resp->lid_angle));
	if (ret) {
		dev_warn(&indio_dev->dev, "Unable to read lid angle\n");
		return ret;
	}

	*data = st->resp->lid_angle.value;
	return 0;
}