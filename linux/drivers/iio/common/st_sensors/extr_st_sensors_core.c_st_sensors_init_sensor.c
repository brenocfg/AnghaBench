#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_8__ ;
typedef  struct TYPE_15__   TYPE_7__ ;
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u8 ;
struct st_sensors_platform_data {int dummy; } ;
struct st_sensor_data {int drdy_int_pin; TYPE_7__* sensor_settings; scalar_t__ int_pin_open_drain; int /*<<< orphan*/  odr; TYPE_1__* current_fullscale; } ;
struct TYPE_16__ {int /*<<< orphan*/  parent; } ;
struct iio_dev {TYPE_8__ dev; } ;
struct TYPE_13__ {scalar_t__ mask_od; scalar_t__ addr_od; } ;
struct TYPE_12__ {scalar_t__ mask_od; scalar_t__ addr_od; } ;
struct TYPE_14__ {TYPE_5__ int2; TYPE_4__ int1; } ;
struct TYPE_11__ {scalar_t__ mask; scalar_t__ addr; } ;
struct TYPE_10__ {scalar_t__ mask; scalar_t__ addr; } ;
struct TYPE_15__ {TYPE_6__ drdy_irq; TYPE_3__ das; TYPE_2__ bdu; } ;
struct TYPE_9__ {int /*<<< orphan*/  num; } ;

/* Variables and functions */
 int /*<<< orphan*/  ST_SENSORS_ENABLE_ALL_AXIS ; 
 int /*<<< orphan*/  dev_info (TYPE_8__*,char*,...) ; 
 struct st_sensor_data* iio_priv (struct iio_dev*) ; 
 struct st_sensors_platform_data* st_sensors_of_probe (int /*<<< orphan*/ ,struct st_sensors_platform_data*) ; 
 int st_sensors_set_axis_enable (struct iio_dev*,int /*<<< orphan*/ ) ; 
 int st_sensors_set_dataready_irq (struct iio_dev*,int) ; 
 int st_sensors_set_drdy_int_pin (struct iio_dev*,struct st_sensors_platform_data*) ; 
 int st_sensors_set_enable (struct iio_dev*,int) ; 
 int st_sensors_set_fullscale (struct iio_dev*,int /*<<< orphan*/ ) ; 
 int st_sensors_set_odr (struct iio_dev*,int /*<<< orphan*/ ) ; 
 int st_sensors_write_data_with_mask (struct iio_dev*,scalar_t__,scalar_t__,int) ; 

int st_sensors_init_sensor(struct iio_dev *indio_dev,
					struct st_sensors_platform_data *pdata)
{
	struct st_sensor_data *sdata = iio_priv(indio_dev);
	struct st_sensors_platform_data *of_pdata;
	int err = 0;

	/* If OF/DT pdata exists, it will take precedence of anything else */
	of_pdata = st_sensors_of_probe(indio_dev->dev.parent, pdata);
	if (of_pdata)
		pdata = of_pdata;

	if (pdata) {
		err = st_sensors_set_drdy_int_pin(indio_dev, pdata);
		if (err < 0)
			return err;
	}

	err = st_sensors_set_enable(indio_dev, false);
	if (err < 0)
		return err;

	/* Disable DRDY, this might be still be enabled after reboot. */
	err = st_sensors_set_dataready_irq(indio_dev, false);
	if (err < 0)
		return err;

	if (sdata->current_fullscale) {
		err = st_sensors_set_fullscale(indio_dev,
						sdata->current_fullscale->num);
		if (err < 0)
			return err;
	} else
		dev_info(&indio_dev->dev, "Full-scale not possible\n");

	err = st_sensors_set_odr(indio_dev, sdata->odr);
	if (err < 0)
		return err;

	/* set BDU */
	if (sdata->sensor_settings->bdu.addr) {
		err = st_sensors_write_data_with_mask(indio_dev,
					sdata->sensor_settings->bdu.addr,
					sdata->sensor_settings->bdu.mask, true);
		if (err < 0)
			return err;
	}

	/* set DAS */
	if (sdata->sensor_settings->das.addr) {
		err = st_sensors_write_data_with_mask(indio_dev,
					sdata->sensor_settings->das.addr,
					sdata->sensor_settings->das.mask, 1);
		if (err < 0)
			return err;
	}

	if (sdata->int_pin_open_drain) {
		u8 addr, mask;

		if (sdata->drdy_int_pin == 1) {
			addr = sdata->sensor_settings->drdy_irq.int1.addr_od;
			mask = sdata->sensor_settings->drdy_irq.int1.mask_od;
		} else {
			addr = sdata->sensor_settings->drdy_irq.int2.addr_od;
			mask = sdata->sensor_settings->drdy_irq.int2.mask_od;
		}

		dev_info(&indio_dev->dev,
			 "set interrupt line to open drain mode on pin %d\n",
			 sdata->drdy_int_pin);
		err = st_sensors_write_data_with_mask(indio_dev, addr,
						      mask, 1);
		if (err < 0)
			return err;
	}

	err = st_sensors_set_axis_enable(indio_dev, ST_SENSORS_ENABLE_ALL_AXIS);

	return err;
}