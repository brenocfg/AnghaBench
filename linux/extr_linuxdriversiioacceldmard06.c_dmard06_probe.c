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
struct TYPE_2__ {int /*<<< orphan*/ * parent; } ;
struct iio_dev {int /*<<< orphan*/ * info; int /*<<< orphan*/  num_channels; int /*<<< orphan*/  channels; int /*<<< orphan*/  modes; int /*<<< orphan*/  name; TYPE_1__ dev; } ;
struct i2c_device_id {int dummy; } ;
struct i2c_client {int /*<<< orphan*/  dev; int /*<<< orphan*/  adapter; } ;
struct dmard06_data {int chip_id; struct i2c_client* client; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int DMARD05_CHIP_ID ; 
 int DMARD06_CHIP_ID ; 
 int /*<<< orphan*/  DMARD06_CHIP_ID_REG ; 
 int /*<<< orphan*/  DMARD06_DRV_NAME ; 
 int DMARD07_CHIP_ID ; 
 int ENODEV ; 
 int ENOMEM ; 
 int ENXIO ; 
 int /*<<< orphan*/  I2C_FUNC_I2C ; 
 int /*<<< orphan*/  INDIO_DIRECT_MODE ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,...) ; 
 struct iio_dev* devm_iio_device_alloc (int /*<<< orphan*/ *,int) ; 
 int devm_iio_device_register (int /*<<< orphan*/ *,struct iio_dev*) ; 
 int /*<<< orphan*/  dmard06_channels ; 
 int /*<<< orphan*/  dmard06_info ; 
 int /*<<< orphan*/  i2c_check_functionality (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i2c_set_clientdata (struct i2c_client*,struct iio_dev*) ; 
 int i2c_smbus_read_byte_data (struct i2c_client*,int /*<<< orphan*/ ) ; 
 struct dmard06_data* iio_priv (struct iio_dev*) ; 

__attribute__((used)) static int dmard06_probe(struct i2c_client *client,
			const struct i2c_device_id *id)
{
	int ret;
	struct iio_dev *indio_dev;
	struct dmard06_data *dmard06;

	if (!i2c_check_functionality(client->adapter, I2C_FUNC_I2C)) {
		dev_err(&client->dev, "I2C check functionality failed\n");
		return -ENXIO;
	}

	indio_dev = devm_iio_device_alloc(&client->dev, sizeof(*dmard06));
	if (!indio_dev) {
		dev_err(&client->dev, "Failed to allocate iio device\n");
		return -ENOMEM;
	}

	dmard06 = iio_priv(indio_dev);
	dmard06->client = client;

	ret = i2c_smbus_read_byte_data(dmard06->client, DMARD06_CHIP_ID_REG);
	if (ret < 0) {
		dev_err(&client->dev, "Error reading chip id: %d\n", ret);
		return ret;
	}

	if (ret != DMARD05_CHIP_ID && ret != DMARD06_CHIP_ID &&
	    ret != DMARD07_CHIP_ID) {
		dev_err(&client->dev, "Invalid chip id: %02d\n", ret);
		return -ENODEV;
	}

	dmard06->chip_id = ret;

	i2c_set_clientdata(client, indio_dev);
	indio_dev->dev.parent = &client->dev;
	indio_dev->name = DMARD06_DRV_NAME;
	indio_dev->modes = INDIO_DIRECT_MODE;
	indio_dev->channels = dmard06_channels;
	indio_dev->num_channels = ARRAY_SIZE(dmard06_channels);
	indio_dev->info = &dmard06_info;

	return devm_iio_device_register(&client->dev, indio_dev);
}