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
struct iio_dev {int /*<<< orphan*/  modes; int /*<<< orphan*/  num_channels; int /*<<< orphan*/  channels; int /*<<< orphan*/  name; int /*<<< orphan*/ * info; TYPE_1__ dev; } ;
struct i2c_device_id {int dummy; } ;
struct i2c_client {int /*<<< orphan*/  dev; } ;
struct al3320a_data {struct i2c_client* client; } ;

/* Variables and functions */
 int /*<<< orphan*/  AL3320A_DRV_NAME ; 
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  INDIO_DIRECT_MODE ; 
 int /*<<< orphan*/  al3320a_channels ; 
 int /*<<< orphan*/  al3320a_info ; 
 int al3320a_init (struct al3320a_data*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 struct iio_dev* devm_iio_device_alloc (int /*<<< orphan*/ *,int) ; 
 int devm_iio_device_register (int /*<<< orphan*/ *,struct iio_dev*) ; 
 int /*<<< orphan*/  i2c_set_clientdata (struct i2c_client*,struct iio_dev*) ; 
 struct al3320a_data* iio_priv (struct iio_dev*) ; 

__attribute__((used)) static int al3320a_probe(struct i2c_client *client,
			 const struct i2c_device_id *id)
{
	struct al3320a_data *data;
	struct iio_dev *indio_dev;
	int ret;

	indio_dev = devm_iio_device_alloc(&client->dev, sizeof(*data));
	if (!indio_dev)
		return -ENOMEM;

	data = iio_priv(indio_dev);
	i2c_set_clientdata(client, indio_dev);
	data->client = client;

	indio_dev->dev.parent = &client->dev;
	indio_dev->info = &al3320a_info;
	indio_dev->name = AL3320A_DRV_NAME;
	indio_dev->channels = al3320a_channels;
	indio_dev->num_channels = ARRAY_SIZE(al3320a_channels);
	indio_dev->modes = INDIO_DIRECT_MODE;

	ret = al3320a_init(data);
	if (ret < 0) {
		dev_err(&client->dev, "al3320a chip init failed\n");
		return ret;
	}
	return devm_iio_device_register(&client->dev, indio_dev);
}