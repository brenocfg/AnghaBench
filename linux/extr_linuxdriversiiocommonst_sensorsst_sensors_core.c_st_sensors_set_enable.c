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
typedef  int /*<<< orphan*/  u8 ;
struct st_sensor_odr_avl {int /*<<< orphan*/  hz; int /*<<< orphan*/  value; int /*<<< orphan*/  member_1; int /*<<< orphan*/  member_0; } ;
struct st_sensor_data {int enabled; TYPE_3__* sensor_settings; int /*<<< orphan*/  odr; } ;
struct iio_dev {int dummy; } ;
struct TYPE_5__ {scalar_t__ addr; scalar_t__ mask; int /*<<< orphan*/  value_off; int /*<<< orphan*/  value_on; } ;
struct TYPE_4__ {scalar_t__ addr; scalar_t__ mask; } ;
struct TYPE_6__ {TYPE_2__ pw; TYPE_1__ odr; } ;

/* Variables and functions */
 int EINVAL ; 
 struct st_sensor_data* iio_priv (struct iio_dev*) ; 
 int st_sensors_match_odr (TYPE_3__*,int /*<<< orphan*/ ,struct st_sensor_odr_avl*) ; 
 int st_sensors_write_data_with_mask (struct iio_dev*,scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 

int st_sensors_set_enable(struct iio_dev *indio_dev, bool enable)
{
	u8 tmp_value;
	int err = -EINVAL;
	bool found = false;
	struct st_sensor_odr_avl odr_out = {0, 0};
	struct st_sensor_data *sdata = iio_priv(indio_dev);

	if (enable) {
		tmp_value = sdata->sensor_settings->pw.value_on;
		if ((sdata->sensor_settings->odr.addr ==
					sdata->sensor_settings->pw.addr) &&
				(sdata->sensor_settings->odr.mask ==
					sdata->sensor_settings->pw.mask)) {
			err = st_sensors_match_odr(sdata->sensor_settings,
							sdata->odr, &odr_out);
			if (err < 0)
				goto set_enable_error;
			tmp_value = odr_out.value;
			found = true;
		}
		err = st_sensors_write_data_with_mask(indio_dev,
				sdata->sensor_settings->pw.addr,
				sdata->sensor_settings->pw.mask, tmp_value);
		if (err < 0)
			goto set_enable_error;

		sdata->enabled = true;

		if (found)
			sdata->odr = odr_out.hz;
	} else {
		err = st_sensors_write_data_with_mask(indio_dev,
				sdata->sensor_settings->pw.addr,
				sdata->sensor_settings->pw.mask,
				sdata->sensor_settings->pw.value_off);
		if (err < 0)
			goto set_enable_error;

		sdata->enabled = false;
	}

set_enable_error:
	return err;
}