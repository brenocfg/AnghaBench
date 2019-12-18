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
struct TYPE_3__ {int /*<<< orphan*/ * parent; } ;
struct iio_dev {int /*<<< orphan*/  modes; int /*<<< orphan*/  num_channels; int /*<<< orphan*/  channels; int /*<<< orphan*/  name; int /*<<< orphan*/ * info; TYPE_1__ dev; } ;
struct i2c_device_id {size_t driver_data; int /*<<< orphan*/  name; } ;
struct i2c_client {int /*<<< orphan*/  dev; int /*<<< orphan*/  adapter; } ;
struct bh1750_data {int /*<<< orphan*/  lock; TYPE_2__* chip_info; struct i2c_client* client; } ;
struct TYPE_4__ {int mtreg_to_usec; int mtreg_default; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int ENOMEM ; 
 int EOPNOTSUPP ; 
 int I2C_FUNC_I2C ; 
 int I2C_FUNC_SMBUS_WRITE_BYTE ; 
 int /*<<< orphan*/  INDIO_DIRECT_MODE ; 
 int bh1750_change_int_time (struct bh1750_data*,int) ; 
 int /*<<< orphan*/  bh1750_channels ; 
 TYPE_2__* bh1750_chip_info_tbl ; 
 int /*<<< orphan*/  bh1750_info ; 
 struct iio_dev* devm_iio_device_alloc (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  i2c_check_functionality (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  i2c_set_clientdata (struct i2c_client*,struct iio_dev*) ; 
 int iio_device_register (struct iio_dev*) ; 
 struct bh1750_data* iio_priv (struct iio_dev*) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int bh1750_probe(struct i2c_client *client,
			const struct i2c_device_id *id)
{
	int ret, usec;
	struct bh1750_data *data;
	struct iio_dev *indio_dev;

	if (!i2c_check_functionality(client->adapter, I2C_FUNC_I2C |
				I2C_FUNC_SMBUS_WRITE_BYTE))
		return -EOPNOTSUPP;

	indio_dev = devm_iio_device_alloc(&client->dev, sizeof(*data));
	if (!indio_dev)
		return -ENOMEM;

	data = iio_priv(indio_dev);
	i2c_set_clientdata(client, indio_dev);
	data->client = client;
	data->chip_info = &bh1750_chip_info_tbl[id->driver_data];

	usec = data->chip_info->mtreg_to_usec * data->chip_info->mtreg_default;
	ret = bh1750_change_int_time(data, usec);
	if (ret < 0)
		return ret;

	mutex_init(&data->lock);
	indio_dev->dev.parent = &client->dev;
	indio_dev->info = &bh1750_info;
	indio_dev->name = id->name;
	indio_dev->channels = bh1750_channels;
	indio_dev->num_channels = ARRAY_SIZE(bh1750_channels);
	indio_dev->modes = INDIO_DIRECT_MODE;

	return iio_device_register(indio_dev);
}