#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct st_sensor_data {int /*<<< orphan*/  get_irq_data_ready; int /*<<< orphan*/ * tf; int /*<<< orphan*/ * dev; } ;
struct TYPE_2__ {int /*<<< orphan*/ * parent; } ;
struct iio_dev {int /*<<< orphan*/  name; TYPE_1__ dev; } ;
struct i2c_client {int /*<<< orphan*/  dev; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  i2c_set_clientdata (struct i2c_client*,struct iio_dev*) ; 
 int /*<<< orphan*/  st_sensors_i2c_get_irq ; 
 int /*<<< orphan*/  st_sensors_tf_i2c ; 

void st_sensors_i2c_configure(struct iio_dev *indio_dev,
		struct i2c_client *client, struct st_sensor_data *sdata)
{
	i2c_set_clientdata(client, indio_dev);

	indio_dev->dev.parent = &client->dev;
	indio_dev->name = client->name;

	sdata->dev = &client->dev;
	sdata->tf = &st_sensors_tf_i2c;
	sdata->get_irq_data_ready = st_sensors_i2c_get_irq;
}