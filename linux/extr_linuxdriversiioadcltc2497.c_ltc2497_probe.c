#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct ltc2497_st {int /*<<< orphan*/  ref; int /*<<< orphan*/  time_prev; int /*<<< orphan*/  addr_prev; struct i2c_client* client; } ;
struct iio_map {int dummy; } ;
struct TYPE_5__ {TYPE_1__* parent; } ;
struct iio_dev {TYPE_3__ dev; int /*<<< orphan*/  num_channels; int /*<<< orphan*/  channels; int /*<<< orphan*/  modes; int /*<<< orphan*/ * info; int /*<<< orphan*/  name; } ;
struct i2c_device_id {int /*<<< orphan*/  name; } ;
struct TYPE_4__ {scalar_t__ platform_data; } ;
struct i2c_client {TYPE_1__ dev; int /*<<< orphan*/  adapter; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int ENOMEM ; 
 int EOPNOTSUPP ; 
 int I2C_FUNC_I2C ; 
 int I2C_FUNC_SMBUS_WRITE_BYTE ; 
 int /*<<< orphan*/  INDIO_DIRECT_MODE ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LTC2497_CONFIG_DEFAULT ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (TYPE_3__*,char*,int) ; 
 struct iio_dev* devm_iio_device_alloc (TYPE_1__*,int) ; 
 int /*<<< orphan*/  devm_regulator_get (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  i2c_check_functionality (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  i2c_set_clientdata (struct i2c_client*,struct iio_dev*) ; 
 int i2c_smbus_write_byte (struct i2c_client*,int /*<<< orphan*/ ) ; 
 int iio_device_register (struct iio_dev*) ; 
 int iio_map_array_register (struct iio_dev*,struct iio_map*) ; 
 int /*<<< orphan*/  iio_map_array_unregister (struct iio_dev*) ; 
 struct ltc2497_st* iio_priv (struct iio_dev*) ; 
 int /*<<< orphan*/  ktime_get () ; 
 int /*<<< orphan*/  ltc2497_channel ; 
 int /*<<< orphan*/  ltc2497_info ; 
 int /*<<< orphan*/  regulator_disable (int /*<<< orphan*/ ) ; 
 int regulator_enable (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ltc2497_probe(struct i2c_client *client,
			 const struct i2c_device_id *id)
{
	struct iio_dev *indio_dev;
	struct ltc2497_st *st;
	struct iio_map *plat_data;
	int ret;

	if (!i2c_check_functionality(client->adapter, I2C_FUNC_I2C |
				     I2C_FUNC_SMBUS_WRITE_BYTE))
		return -EOPNOTSUPP;

	indio_dev = devm_iio_device_alloc(&client->dev, sizeof(*st));
	if (!indio_dev)
		return -ENOMEM;

	st = iio_priv(indio_dev);
	i2c_set_clientdata(client, indio_dev);
	st->client = client;

	indio_dev->dev.parent = &client->dev;
	indio_dev->name = id->name;
	indio_dev->info = &ltc2497_info;
	indio_dev->modes = INDIO_DIRECT_MODE;
	indio_dev->channels = ltc2497_channel;
	indio_dev->num_channels = ARRAY_SIZE(ltc2497_channel);

	st->ref = devm_regulator_get(&client->dev, "vref");
	if (IS_ERR(st->ref))
		return PTR_ERR(st->ref);

	ret = regulator_enable(st->ref);
	if (ret < 0)
		return ret;

	if (client->dev.platform_data) {
		plat_data = ((struct iio_map *)client->dev.platform_data);
		ret = iio_map_array_register(indio_dev, plat_data);
		if (ret) {
			dev_err(&indio_dev->dev, "iio map err: %d\n", ret);
			goto err_regulator_disable;
		}
	}

	ret = i2c_smbus_write_byte(st->client, LTC2497_CONFIG_DEFAULT);
	if (ret < 0)
		goto err_array_unregister;

	st->addr_prev = LTC2497_CONFIG_DEFAULT;
	st->time_prev = ktime_get();

	ret = iio_device_register(indio_dev);
	if (ret < 0)
		goto err_array_unregister;

	return 0;

err_array_unregister:
	iio_map_array_unregister(indio_dev);

err_regulator_disable:
	regulator_disable(st->ref);

	return ret;
}