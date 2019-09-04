#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct st_sensor_data {int dummy; } ;
struct iio_dev {int dummy; } ;
struct i2c_device_id {int dummy; } ;
struct TYPE_6__ {scalar_t__ of_node; } ;
struct i2c_client {int /*<<< orphan*/  name; TYPE_1__ dev; } ;
struct TYPE_7__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 scalar_t__ ACPI_HANDLE (TYPE_1__*) ; 
 int ENODEV ; 
 int ENOMEM ; 
 int ST_PRESS_MAX ; 
 struct iio_dev* devm_iio_device_alloc (TYPE_1__*,int) ; 
 struct st_sensor_data* iio_priv (struct iio_dev*) ; 
 int st_press_common_probe (struct iio_dev*) ; 
 TYPE_3__* st_press_id_table ; 
 int /*<<< orphan*/  st_press_of_match ; 
 int /*<<< orphan*/  st_sensors_i2c_configure (struct iio_dev*,struct i2c_client*,struct st_sensor_data*) ; 
 int st_sensors_match_acpi_device (TYPE_1__*) ; 
 int /*<<< orphan*/  st_sensors_of_name_probe (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int st_press_i2c_probe(struct i2c_client *client,
						const struct i2c_device_id *id)
{
	struct iio_dev *indio_dev;
	struct st_sensor_data *press_data;
	int ret;

	indio_dev = devm_iio_device_alloc(&client->dev, sizeof(*press_data));
	if (!indio_dev)
		return -ENOMEM;

	press_data = iio_priv(indio_dev);

	if (client->dev.of_node) {
		st_sensors_of_name_probe(&client->dev, st_press_of_match,
					 client->name, sizeof(client->name));
	} else if (ACPI_HANDLE(&client->dev)) {
		ret = st_sensors_match_acpi_device(&client->dev);
		if ((ret < 0) || (ret >= ST_PRESS_MAX))
			return -ENODEV;

		strlcpy(client->name, st_press_id_table[ret].name,
				sizeof(client->name));
	} else if (!id)
		return -ENODEV;

	st_sensors_i2c_configure(indio_dev, client, press_data);

	ret = st_press_common_probe(indio_dev);
	if (ret < 0)
		return ret;

	return 0;
}