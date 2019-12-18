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
struct st_sensor_data {int /*<<< orphan*/  irq; int /*<<< orphan*/ * dev; int /*<<< orphan*/  regmap; TYPE_1__* sensor_settings; } ;
struct regmap_config {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/ * parent; } ;
struct iio_dev {int /*<<< orphan*/  name; TYPE_2__ dev; } ;
struct i2c_client {int /*<<< orphan*/  irq; int /*<<< orphan*/  dev; int /*<<< orphan*/  name; } ;
struct TYPE_3__ {scalar_t__ multi_read_bit; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  devm_regmap_init_i2c (struct i2c_client*,struct regmap_config const*) ; 
 int /*<<< orphan*/  i2c_set_clientdata (struct i2c_client*,struct iio_dev*) ; 
 struct st_sensor_data* iio_priv (struct iio_dev*) ; 
 struct regmap_config st_sensors_i2c_regmap_config ; 
 struct regmap_config st_sensors_i2c_regmap_multiread_bit_config ; 

int st_sensors_i2c_configure(struct iio_dev *indio_dev,
			     struct i2c_client *client)
{
	struct st_sensor_data *sdata = iio_priv(indio_dev);
	const struct regmap_config *config;

	if (sdata->sensor_settings->multi_read_bit)
		config = &st_sensors_i2c_regmap_multiread_bit_config;
	else
		config = &st_sensors_i2c_regmap_config;

	sdata->regmap = devm_regmap_init_i2c(client, config);
	if (IS_ERR(sdata->regmap)) {
		dev_err(&client->dev, "Failed to register i2c regmap (%d)\n",
			(int)PTR_ERR(sdata->regmap));
		return PTR_ERR(sdata->regmap);
	}

	i2c_set_clientdata(client, indio_dev);

	indio_dev->dev.parent = &client->dev;
	indio_dev->name = client->name;

	sdata->dev = &client->dev;
	sdata->irq = client->irq;

	return 0;
}