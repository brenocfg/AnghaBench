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
struct st_sensors_platform_data {scalar_t__ spi_3wire; } ;
struct TYPE_5__ {int /*<<< orphan*/  value; scalar_t__ addr; } ;
struct st_sensor_settings {TYPE_2__ sim; } ;
struct st_sensor_data {TYPE_3__* dev; int /*<<< orphan*/  tb; TYPE_1__* tf; } ;
struct iio_dev {int /*<<< orphan*/  dev; } ;
struct device_node {int dummy; } ;
struct TYPE_6__ {scalar_t__ platform_data; struct device_node* of_node; } ;
struct TYPE_4__ {int (* write_byte ) (int /*<<< orphan*/ *,TYPE_3__*,scalar_t__,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 struct st_sensor_data* iio_priv (struct iio_dev*) ; 
 scalar_t__ of_property_read_bool (struct device_node*,char*) ; 
 int stub1 (int /*<<< orphan*/ *,TYPE_3__*,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int st_sensors_init_interface_mode(struct iio_dev *indio_dev,
			const struct st_sensor_settings *sensor_settings)
{
	struct st_sensor_data *sdata = iio_priv(indio_dev);
	struct device_node *np = sdata->dev->of_node;
	struct st_sensors_platform_data *pdata;

	pdata = (struct st_sensors_platform_data *)sdata->dev->platform_data;
	if (((np && of_property_read_bool(np, "spi-3wire")) ||
	     (pdata && pdata->spi_3wire)) && sensor_settings->sim.addr) {
		int err;

		err = sdata->tf->write_byte(&sdata->tb, sdata->dev,
					    sensor_settings->sim.addr,
					    sensor_settings->sim.value);
		if (err < 0) {
			dev_err(&indio_dev->dev,
				"failed to init interface mode\n");
			return err;
		}
	}

	return 0;
}