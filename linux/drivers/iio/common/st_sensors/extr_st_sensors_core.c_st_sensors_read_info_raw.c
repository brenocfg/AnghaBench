#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct st_sensor_data {int odr; TYPE_1__* sensor_settings; } ;
struct iio_dev {scalar_t__ currentmode; int /*<<< orphan*/  mlock; } ;
struct TYPE_4__ {int shift; } ;
struct iio_chan_spec {TYPE_2__ scan_type; } ;
struct TYPE_3__ {int bootime; } ;

/* Variables and functions */
 int EBUSY ; 
 scalar_t__ INDIO_BUFFER_TRIGGERED ; 
 struct st_sensor_data* iio_priv (struct iio_dev*) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int st_sensors_read_axis_data (struct iio_dev*,struct iio_chan_spec const*,int*) ; 
 int st_sensors_set_enable (struct iio_dev*,int) ; 

int st_sensors_read_info_raw(struct iio_dev *indio_dev,
				struct iio_chan_spec const *ch, int *val)
{
	int err;
	struct st_sensor_data *sdata = iio_priv(indio_dev);

	mutex_lock(&indio_dev->mlock);
	if (indio_dev->currentmode == INDIO_BUFFER_TRIGGERED) {
		err = -EBUSY;
		goto out;
	} else {
		err = st_sensors_set_enable(indio_dev, true);
		if (err < 0)
			goto out;

		msleep((sdata->sensor_settings->bootime * 1000) / sdata->odr);
		err = st_sensors_read_axis_data(indio_dev, ch, val);
		if (err < 0)
			goto out;

		*val = *val >> ch->scan_type.shift;

		err = st_sensors_set_enable(indio_dev, false);
	}
out:
	mutex_unlock(&indio_dev->mlock);

	return err;
}