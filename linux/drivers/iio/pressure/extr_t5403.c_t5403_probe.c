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
typedef  int /*<<< orphan*/  u8 ;
struct t5403_data {scalar_t__ c; struct i2c_client* client; int /*<<< orphan*/  mode; int /*<<< orphan*/  lock; } ;
struct TYPE_2__ {int /*<<< orphan*/ * parent; } ;
struct iio_dev {int /*<<< orphan*/  num_channels; int /*<<< orphan*/  channels; int /*<<< orphan*/  modes; TYPE_1__ dev; int /*<<< orphan*/  name; int /*<<< orphan*/ * info; } ;
struct i2c_device_id {int /*<<< orphan*/  name; } ;
struct i2c_client {int /*<<< orphan*/  dev; int /*<<< orphan*/  adapter; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int ENODEV ; 
 int ENOMEM ; 
 int EOPNOTSUPP ; 
 int I2C_FUNC_SMBUS_I2C_BLOCK ; 
 int I2C_FUNC_SMBUS_WORD_DATA ; 
 int /*<<< orphan*/  INDIO_DIRECT_MODE ; 
 int /*<<< orphan*/  T5403_CALIB_DATA ; 
 int T5403_I2C_ADDR ; 
 int T5403_I2C_MASK ; 
 int /*<<< orphan*/  T5403_MODE_STANDARD ; 
 int /*<<< orphan*/  T5403_SLAVE_ADDR ; 
 struct iio_dev* devm_iio_device_alloc (int /*<<< orphan*/ *,int) ; 
 int devm_iio_device_register (int /*<<< orphan*/ *,struct iio_dev*) ; 
 int /*<<< orphan*/  i2c_check_functionality (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  i2c_set_clientdata (struct i2c_client*,struct iio_dev*) ; 
 int i2c_smbus_read_byte_data (struct i2c_client*,int /*<<< orphan*/ ) ; 
 int i2c_smbus_read_i2c_block_data (struct i2c_client*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 struct t5403_data* iio_priv (struct iio_dev*) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  t5403_channels ; 
 int /*<<< orphan*/  t5403_info ; 

__attribute__((used)) static int t5403_probe(struct i2c_client *client,
			 const struct i2c_device_id *id)
{
	struct t5403_data *data;
	struct iio_dev *indio_dev;
	int ret;

	if (!i2c_check_functionality(client->adapter, I2C_FUNC_SMBUS_WORD_DATA |
	    I2C_FUNC_SMBUS_I2C_BLOCK))
		return -EOPNOTSUPP;

	ret = i2c_smbus_read_byte_data(client, T5403_SLAVE_ADDR);
	if (ret < 0)
		return ret;
	if ((ret & T5403_I2C_MASK) != T5403_I2C_ADDR)
		return -ENODEV;

	indio_dev = devm_iio_device_alloc(&client->dev, sizeof(*data));
	if (!indio_dev)
		return -ENOMEM;

	data = iio_priv(indio_dev);
	data->client = client;
	mutex_init(&data->lock);

	i2c_set_clientdata(client, indio_dev);
	indio_dev->info = &t5403_info;
	indio_dev->name = id->name;
	indio_dev->dev.parent = &client->dev;
	indio_dev->modes = INDIO_DIRECT_MODE;
	indio_dev->channels = t5403_channels;
	indio_dev->num_channels = ARRAY_SIZE(t5403_channels);

	data->mode = T5403_MODE_STANDARD;

	ret = i2c_smbus_read_i2c_block_data(data->client, T5403_CALIB_DATA,
	    sizeof(data->c), (u8 *) data->c);
	if (ret < 0)
		return ret;

	return devm_iio_device_register(&client->dev, indio_dev);
}