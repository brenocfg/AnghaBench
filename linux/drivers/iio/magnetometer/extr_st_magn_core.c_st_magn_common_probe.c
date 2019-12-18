#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct st_sensor_fullscale_avl {int dummy; } ;
struct st_sensor_data {scalar_t__ irq; TYPE_4__* sensor_settings; int /*<<< orphan*/  odr; struct st_sensor_fullscale_avl* current_fullscale; int /*<<< orphan*/  num_data_channels; } ;
struct iio_dev {int /*<<< orphan*/  name; int /*<<< orphan*/  dev; int /*<<< orphan*/  num_channels; int /*<<< orphan*/  channels; int /*<<< orphan*/ * info; int /*<<< orphan*/  modes; } ;
struct TYPE_7__ {TYPE_2__* odr_avl; } ;
struct TYPE_5__ {int /*<<< orphan*/ * fs_avl; } ;
struct TYPE_8__ {TYPE_3__ odr; TYPE_1__ fs; int /*<<< orphan*/  ch; } ;
struct TYPE_6__ {int /*<<< orphan*/  hz; } ;

/* Variables and functions */
 int /*<<< orphan*/  INDIO_DIRECT_MODE ; 
 int /*<<< orphan*/  ST_MAGN_NUMBER_DATA_CHANNELS ; 
 int /*<<< orphan*/  ST_MAGN_TRIGGER_OPS ; 
 int /*<<< orphan*/  ST_SENSORS_NUMBER_ALL_CHANNELS ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int iio_device_register (struct iio_dev*) ; 
 struct st_sensor_data* iio_priv (struct iio_dev*) ; 
 int /*<<< orphan*/  magn_info ; 
 int st_magn_allocate_ring (struct iio_dev*) ; 
 int /*<<< orphan*/  st_magn_deallocate_ring (struct iio_dev*) ; 
 int st_sensors_allocate_trigger (struct iio_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  st_sensors_deallocate_trigger (struct iio_dev*) ; 
 int st_sensors_init_sensor (struct iio_dev*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  st_sensors_power_disable (struct iio_dev*) ; 
 int st_sensors_power_enable (struct iio_dev*) ; 
 int st_sensors_verify_id (struct iio_dev*) ; 

int st_magn_common_probe(struct iio_dev *indio_dev)
{
	struct st_sensor_data *mdata = iio_priv(indio_dev);
	int err;

	indio_dev->modes = INDIO_DIRECT_MODE;
	indio_dev->info = &magn_info;

	err = st_sensors_power_enable(indio_dev);
	if (err)
		return err;

	err = st_sensors_verify_id(indio_dev);
	if (err < 0)
		goto st_magn_power_off;

	mdata->num_data_channels = ST_MAGN_NUMBER_DATA_CHANNELS;
	indio_dev->channels = mdata->sensor_settings->ch;
	indio_dev->num_channels = ST_SENSORS_NUMBER_ALL_CHANNELS;

	mdata->current_fullscale = (struct st_sensor_fullscale_avl *)
					&mdata->sensor_settings->fs.fs_avl[0];
	mdata->odr = mdata->sensor_settings->odr.odr_avl[0].hz;

	err = st_sensors_init_sensor(indio_dev, NULL);
	if (err < 0)
		goto st_magn_power_off;

	err = st_magn_allocate_ring(indio_dev);
	if (err < 0)
		goto st_magn_power_off;

	if (mdata->irq > 0) {
		err = st_sensors_allocate_trigger(indio_dev,
						ST_MAGN_TRIGGER_OPS);
		if (err < 0)
			goto st_magn_probe_trigger_error;
	}

	err = iio_device_register(indio_dev);
	if (err)
		goto st_magn_device_register_error;

	dev_info(&indio_dev->dev, "registered magnetometer %s\n",
		 indio_dev->name);

	return 0;

st_magn_device_register_error:
	if (mdata->irq > 0)
		st_sensors_deallocate_trigger(indio_dev);
st_magn_probe_trigger_error:
	st_magn_deallocate_ring(indio_dev);
st_magn_power_off:
	st_sensors_power_disable(indio_dev);

	return err;
}