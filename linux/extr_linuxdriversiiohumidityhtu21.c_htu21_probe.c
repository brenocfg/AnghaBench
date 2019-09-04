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
typedef  int /*<<< orphan*/  u64 ;
struct ms_ht_dev {int /*<<< orphan*/  lock; scalar_t__ res_index; struct i2c_client* client; } ;
struct TYPE_2__ {int /*<<< orphan*/ * parent; } ;
struct iio_dev {void* num_channels; void* channels; int /*<<< orphan*/  modes; TYPE_1__ dev; int /*<<< orphan*/  name; int /*<<< orphan*/ * info; } ;
struct i2c_device_id {scalar_t__ driver_data; int /*<<< orphan*/  name; } ;
struct i2c_client {int /*<<< orphan*/  dev; int /*<<< orphan*/  adapter; } ;

/* Variables and functions */
 void* ARRAY_SIZE (void*) ; 
 int ENOMEM ; 
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  HTU21_RESET ; 
 int I2C_FUNC_SMBUS_READ_I2C_BLOCK ; 
 int I2C_FUNC_SMBUS_WRITE_BYTE ; 
 int I2C_FUNC_SMBUS_WRITE_BYTE_DATA ; 
 int /*<<< orphan*/  INDIO_DIRECT_MODE ; 
 scalar_t__ MS8607 ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 struct iio_dev* devm_iio_device_alloc (int /*<<< orphan*/ *,int) ; 
 int devm_iio_device_register (int /*<<< orphan*/ *,struct iio_dev*) ; 
 void* htu21_channels ; 
 int /*<<< orphan*/  htu21_info ; 
 int /*<<< orphan*/  i2c_check_functionality (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  i2c_set_clientdata (struct i2c_client*,struct iio_dev*) ; 
 struct ms_ht_dev* iio_priv (struct iio_dev*) ; 
 void* ms8607_channels ; 
 int ms_sensors_read_serial (struct i2c_client*,int /*<<< orphan*/ *) ; 
 int ms_sensors_reset (struct i2c_client*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int htu21_probe(struct i2c_client *client,
		       const struct i2c_device_id *id)
{
	struct ms_ht_dev *dev_data;
	struct iio_dev *indio_dev;
	int ret;
	u64 serial_number;

	if (!i2c_check_functionality(client->adapter,
				     I2C_FUNC_SMBUS_WRITE_BYTE_DATA |
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
	dev_data->res_index = 0;
	mutex_init(&dev_data->lock);

	indio_dev->info = &htu21_info;
	indio_dev->name = id->name;
	indio_dev->dev.parent = &client->dev;
	indio_dev->modes = INDIO_DIRECT_MODE;

	if (id->driver_data == MS8607) {
		indio_dev->channels = ms8607_channels;
		indio_dev->num_channels = ARRAY_SIZE(ms8607_channels);
	} else {
		indio_dev->channels = htu21_channels;
		indio_dev->num_channels = ARRAY_SIZE(htu21_channels);
	}

	i2c_set_clientdata(client, indio_dev);

	ret = ms_sensors_reset(client, HTU21_RESET, 15000);
	if (ret)
		return ret;

	ret = ms_sensors_read_serial(client, &serial_number);
	if (ret)
		return ret;
	dev_info(&client->dev, "Serial number : %llx", serial_number);

	return devm_iio_device_register(&client->dev, indio_dev);
}