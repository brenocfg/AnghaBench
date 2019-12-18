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
struct rfd77402_data {int /*<<< orphan*/  lock; struct i2c_client* client; } ;
struct TYPE_2__ {int /*<<< orphan*/ * parent; } ;
struct iio_dev {int /*<<< orphan*/  modes; int /*<<< orphan*/  name; int /*<<< orphan*/  num_channels; int /*<<< orphan*/  channels; int /*<<< orphan*/ * info; TYPE_1__ dev; } ;
struct i2c_device_id {int dummy; } ;
struct i2c_client {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  INDIO_DIRECT_MODE ; 
 int /*<<< orphan*/  RFD77402_DRV_NAME ; 
 int /*<<< orphan*/  RFD77402_MOD_CHIP_ID ; 
 struct iio_dev* devm_iio_device_alloc (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  i2c_set_clientdata (struct i2c_client*,struct iio_dev*) ; 
 int i2c_smbus_read_word_data (struct i2c_client*,int /*<<< orphan*/ ) ; 
 int iio_device_register (struct iio_dev*) ; 
 struct rfd77402_data* iio_priv (struct iio_dev*) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rfd77402_channels ; 
 int /*<<< orphan*/  rfd77402_info ; 
 int rfd77402_init (struct rfd77402_data*) ; 
 int /*<<< orphan*/  rfd77402_powerdown (struct rfd77402_data*) ; 

__attribute__((used)) static int rfd77402_probe(struct i2c_client *client,
			  const struct i2c_device_id *id)
{
	struct rfd77402_data *data;
	struct iio_dev *indio_dev;
	int ret;

	ret = i2c_smbus_read_word_data(client, RFD77402_MOD_CHIP_ID);
	if (ret < 0)
		return ret;
	if (ret != 0xad01 && ret != 0xad02) /* known chip ids */
		return -ENODEV;

	indio_dev = devm_iio_device_alloc(&client->dev, sizeof(*data));
	if (!indio_dev)
		return -ENOMEM;

	data = iio_priv(indio_dev);
	i2c_set_clientdata(client, indio_dev);
	data->client = client;
	mutex_init(&data->lock);

	indio_dev->dev.parent = &client->dev;
	indio_dev->info = &rfd77402_info;
	indio_dev->channels = rfd77402_channels;
	indio_dev->num_channels = ARRAY_SIZE(rfd77402_channels);
	indio_dev->name = RFD77402_DRV_NAME;
	indio_dev->modes = INDIO_DIRECT_MODE;

	ret = rfd77402_init(data);
	if (ret < 0)
		return ret;

	ret = iio_device_register(indio_dev);
	if (ret)
		goto err_powerdown;

	return 0;

err_powerdown:
	rfd77402_powerdown(data);
	return ret;
}