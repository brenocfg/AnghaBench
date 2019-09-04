#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct tsys01_dev {int /*<<< orphan*/  convert_and_read; int /*<<< orphan*/  read_prom_word; int /*<<< orphan*/  reset; struct i2c_client* client; } ;
struct iio_dev {int dummy; } ;
struct i2c_device_id {int dummy; } ;
struct i2c_client {int /*<<< orphan*/  dev; int /*<<< orphan*/  adapter; } ;

/* Variables and functions */
 int ENOMEM ; 
 int EOPNOTSUPP ; 
 int I2C_FUNC_SMBUS_READ_I2C_BLOCK ; 
 int I2C_FUNC_SMBUS_WORD_DATA ; 
 int I2C_FUNC_SMBUS_WRITE_BYTE ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 struct iio_dev* devm_iio_device_alloc (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  i2c_check_functionality (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  i2c_set_clientdata (struct i2c_client*,struct iio_dev*) ; 
 struct tsys01_dev* iio_priv (struct iio_dev*) ; 
 int /*<<< orphan*/  ms_sensors_convert_and_read ; 
 int /*<<< orphan*/  ms_sensors_read_prom_word ; 
 int /*<<< orphan*/  ms_sensors_reset ; 
 int tsys01_probe (struct iio_dev*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int tsys01_i2c_probe(struct i2c_client *client,
			    const struct i2c_device_id *id)
{
	struct tsys01_dev *dev_data;
	struct iio_dev *indio_dev;

	if (!i2c_check_functionality(client->adapter,
				     I2C_FUNC_SMBUS_WORD_DATA |
				     I2C_FUNC_SMBUS_WRITE_BYTE |
				     I2C_FUNC_SMBUS_READ_I2C_BLOCK)) {
		dev_err(&client->dev,
			"Adapter does not support some i2c transaction\n");
		return -EOPNOTSUPP;
	}

	indio_dev = devm_iio_device_alloc(&client->dev, sizeof(*dev_data));
	if (!indio_dev)
		return -ENOMEM;

	dev_data = iio_priv(indio_dev);
	dev_data->client = client;
	dev_data->reset = ms_sensors_reset;
	dev_data->read_prom_word = ms_sensors_read_prom_word;
	dev_data->convert_and_read = ms_sensors_convert_and_read;

	i2c_set_clientdata(client, indio_dev);

	return tsys01_probe(indio_dev, &client->dev);
}